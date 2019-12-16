from django.shortcuts import render
from django.http import HttpResponse
from django.http import HttpResponseRedirect
from django.views.decorators.csrf import csrf_exempt

from facenet_pytorch import MTCNN
import torch
import numpy as np
import cv2
from PIL import Image, ImageDraw
from IPython import display
import io
import time
import os
from PIL import ImageFile

import numpy as np
import random


def white_balance_2(img_input):
    img = img_input.copy()
    b, g, r = cv2.split(img)
    m, n, t = img.shape
    sum_ = np.zeros(b.shape)
    for i in range(m):
        for j in range(n):
            sum_[i][j] = int(b[i][j]) + int(g[i][j]) + int(r[i][j])
    hists, bins = np.histogram(sum_.flatten(), 766, [0, 766])
    Y = 765
    num, key = 0, 0
    ratio = 0.01
    while Y >= 0:
        num += hists[Y]
        if num > m * n * ratio / 100:
            key = Y
            break
        Y = Y - 1

    sum_b, sum_g, sum_r = 0, 0, 0
    time = 0
    for i in range(m):
        for j in range(n):
            if sum_[i][j] >= key:
                sum_b += b[i][j]
                sum_g += g[i][j]
                sum_r += r[i][j]
                time = time + 1

    avg_b = sum_b / time
    avg_g = sum_g / time
    avg_r = sum_r / time

    maxvalue = float(np.max(img))
    # maxvalue = 255
    for i in range(m):
        for j in range(n):
            b = int(img[i][j][0]) * maxvalue / int(avg_b)
            g = int(img[i][j][1]) * maxvalue / int(avg_g)
            r = int(img[i][j][2]) * maxvalue / int(avg_r)
            if b > 255:
                b = 255
            if b < 0:
                b = 0
            if g > 255:
                g = 255
            if g < 0:
                g = 0
            if r > 255:
                r = 255
            if r < 0:
                r = 0
            img[i][j][0] = b
            img[i][j][1] = g
            img[i][j][2] = r

    return img

def white_balance_3(img):
    B, G, R = np.double(img[:, :, 0]), np.double(img[:, :, 1]), np.double(img[:, :, 2])
    B_ave, G_ave, R_ave = np.mean(B), np.mean(G), np.mean(R)
    K = (B_ave + G_ave + R_ave) / 3
    Kb, Kg, Kr = K / B_ave, K / G_ave, K / R_ave
    Ba = (B * Kb)
    Ga = (G * Kg)
    Ra = (R * Kr)

    for i in range(len(Ba)):
        for j in range(len(Ba[0])):
            Ba[i][j] = 255 if Ba[i][j] > 255 else Ba[i][j]
            Ga[i][j] = 255 if Ga[i][j] > 255 else Ga[i][j]
            Ra[i][j] = 255 if Ra[i][j] > 255 else Ra[i][j]

    # print(np.mean(Ba), np.mean(Ga), np.mean(Ra))
    dst_img = np.uint8(np.zeros_like(img))
    dst_img[:, :, 0] = Ba
    dst_img[:, :, 1] = Ga
    dst_img[:, :, 2] = Ra
    return dst_img

def white_balance_4(img):
    def detection(img):
        img_lab = cv2.cvtColor(img, cv2.COLOR_BGR2LAB)
        l, a, b = cv2.split(img_lab)
        d_a, d_b, M_a, M_b = 0, 0, 0, 0
        for i in range(m):
            for j in range(n):
                d_a = d_a + a[i][j]
                d_b = d_b + b[i][j]
        d_a, d_b = (d_a / (m * n)) - 128, (d_b / (n * m)) - 128
        D = np.sqrt((np.square(d_a) + np.square(d_b)))

        for i in range(m):
            for j in range(n):
                M_a = np.abs(a[i][j] - d_a - 128) + M_a
                M_b = np.abs(b[i][j] - d_b - 128) + M_b

        M_a, M_b = M_a / (m * n), M_b / (m * n)
        M = np.sqrt((np.square(M_a) + np.square(M_b)))
        k = D / M
        print('Valud:%f' % k)
        return

    b, g, r = cv2.split(img)
    # print(img.shape)
    m, n = b.shape
    # detection(img)

    I_r_2 = np.zeros(r.shape)
    I_b_2 = np.zeros(b.shape)
    sum_I_r_2, sum_I_r, sum_I_b_2, sum_I_b, sum_I_g = 0, 0, 0, 0, 0
    max_I_r_2, max_I_r, max_I_b_2, max_I_b, max_I_g = int(r[0][0] ** 2), int(r[0][0]), int(b[0][0] ** 2), int(b[0][0]), int(g[0][0])
    for i in range(m):
        for j in range(n):
            I_r_2[i][j] = int(r[i][j] ** 2)
            I_b_2[i][j] = int(b[i][j] ** 2)
            sum_I_r_2 = I_r_2[i][j] + sum_I_r_2
            sum_I_b_2 = I_b_2[i][j] + sum_I_b_2
            sum_I_g = g[i][j] + sum_I_g
            sum_I_r = r[i][j] + sum_I_r
            sum_I_b = b[i][j] + sum_I_b
            if max_I_r < r[i][j]:
                max_I_r = r[i][j]
            if max_I_r_2 < I_r_2[i][j]:
                max_I_r_2 = I_r_2[i][j]
            if max_I_g < g[i][j]:
                max_I_g = g[i][j]
            if max_I_b_2 < I_b_2[i][j]:
                max_I_b_2 = I_b_2[i][j]
            if max_I_b < b[i][j]:
                max_I_b = b[i][j]

    [u_b, v_b] = np.matmul(np.linalg.inv([[sum_I_b_2, sum_I_b], [max_I_b_2, max_I_b]]), [sum_I_g, max_I_g])
    [u_r, v_r] = np.matmul(np.linalg.inv([[sum_I_r_2, sum_I_r], [max_I_r_2, max_I_r]]), [sum_I_g, max_I_g])
    # print(u_b, v_b, u_r, v_r)
    b0, g0, r0 = np.zeros(b.shape, np.uint8), np.zeros(g.shape, np.uint8), np.zeros(r.shape, np.uint8)
    for i in range(m):
        for j in range(n):
            b_point = u_b * (b[i][j] ** 2) + v_b * b[i][j]
            g0[i][j] = g[i][j]
            # r0[i][j] = r[i][j]
            r_point = u_r * (r[i][j] ** 2) + v_r * r[i][j]
            if r_point>255:
                r0[i][j] = 255
            else:
                if r_point<0:
                    r0[i][j] = 0
                else:
                    r0[i][j] = r_point
            if b_point>255:
                b0[i][j] = 255
            else:
                if b_point<0:
                    b0[i][j] = 0
                else:
                    b0[i][j] = b_point
    return cv2.merge([b0, g0, r0])

def white_balance_5(img):
    b, g, r = cv2.split(img)
    def con_num(x):
        if x > 0:
            return 1
        if x < 0:
            return -1
        if x == 0:
            return 0
    yuv_img = cv2.cvtColor(img, cv2.COLOR_BGR2YCrCb)
    (y, u, v) = cv2.split(yuv_img)
    # y, u, v = cv2.split(img)
    m, n = y.shape
    sum_u, sum_v = 0, 0
    max_y = np.max(y.flatten())
    # print(max_y)
    for i in range(m):
        for j in range(n):
            sum_u = sum_u + u[i][j]
            sum_v = sum_v + v[i][j]

    avl_u = sum_u / (m * n)
    avl_v = sum_v / (m * n)
    du, dv = 0, 0
    # print(avl_u, avl_v)
    for i in range(m):
        for j in range(n):
            du = du + np.abs(u[i][j] - avl_u)
            dv = dv + np.abs(v[i][j] - avl_v)

    avl_du = du / (m * n)
    avl_dv = dv / (m * n)
    num_y, yhistogram, ysum = np.zeros(y.shape), np.zeros(256), 0
    radio = 0.5  # 如果该值过大过小，色温向两极端发展
    for i in range(m):
        for j in range(n):
            value = 0
            if np.abs(u[i][j] - (avl_u + avl_du * con_num(avl_u))) < radio * avl_du or np.abs(
                    v[i][j] - (avl_v + avl_dv * con_num(avl_v))) < radio * avl_dv:
                value = 1
            else:
                value = 0

            if value <= 0:
                continue
            num_y[i][j] = y[i][j]
            yhistogram[int(num_y[i][j])] = 1 + yhistogram[int(num_y[i][j])]
            ysum += 1
    # print(yhistogram.shape)
    sum_yhistogram = 0
    # hists2, bins = np.histogram(yhistogram, 256, [0, 256])
    # print(hists2)
    Y = 255
    num, key = 0, 0
    while Y >= 0:
        num += yhistogram[Y]
        if num > 0.1 * ysum:    # 取前10%的亮点为计算值，如果该值过大易过曝光，该值过小调整幅度小
            key = Y
            break
        Y = Y - 1
    # print(key)
    sum_r, sum_g, sum_b, num_rgb = 0, 0, 0, 0
    for i in range(m):
        for j in range(n):
            if num_y[i][j] > key:
                sum_r = sum_r + r[i][j]
                sum_g = sum_g + g[i][j]
                sum_b = sum_b + b[i][j]
                num_rgb += 1

    avl_r = sum_r / num_rgb
    avl_g = sum_g / num_rgb
    avl_b = sum_b / num_rgb

    for i in range(m):
        for j in range(n):
            b_point = int(b[i][j]) * int(max_y) / avl_b
            g_point = int(g[i][j]) * int(max_y) / avl_g
            r_point = int(r[i][j]) * int(max_y) / avl_r
            if b_point>255:
                b[i][j] = 255
            else:
                if b_point<0:
                    b[i][j] = 0
                else:
                    b[i][j] = b_point
            if g_point>255:
                g[i][j] = 255
            else:
                if g_point<0:
                    g[i][j] = 0
                else:
                    g[i][j] = g_point
            if r_point>255:
                r[i][j] = 255
            else:
                if r_point<0:
                    r[i][j] = 0
                else:
                    r[i][j] = r_point

    return cv2.merge([b, g, r])


def hello(request):
    context = {}
    context['content1'] = 'Hello World'
    return render(request, 'helloworld.html', context)


command_state = ['Receive', 'Act']
class Commander():
    def __init__(self):
        self.state = "Receive"
        self.command = "NONE"

commander = Commander()


def acceptCommand(request):
    print(request)

    command_received = 'u' + str(request).split('=')[1][7].lower()

    print("Accept Command from Phone:", command_received)

    if commander.state == 'Receive':
        commander.state = 'Act'
        commander.command = command_received

        return HttpResponse('Successfully Received Your Command')
    else:
        return HttpResponse('Last Command Still Not Finished')

def actCommand(request):
    print(request)

    command_act = ''

    if commander.state == 'Act':
        print('Someone come to acquire its task!')
        command_act = commander.command
        commander.state = 'Receive'
    else:
        print('No new task to allocate!')

    return HttpResponse(command_act)



class imageContainer(object):
    def __init__(self):
        self.start = time.time()
        self.flag = False
        self.image_bytes = b''

image_object = imageContainer()
# image_object_2 = imageContainer()
check = {'t': b'\t', 'n': '\n', '\\': b'\\', 'r': '\r'}
@csrf_exempt
def identify(request):
    context = {}
    context['content'] = request.method

    print('Enter to Identify Page')

    content = request.body
    response = 'ERROR'
    # print("decode content: ", content.decode())
    # print("decode content type:", type(content))

    if content.decode() == '"START"':
        image_object.flag = True
        image_object.image_bytes = b''
        image_object.start = time.time()
        
        try:
            print("delete testing.txt")
            os.remove("./static/img/testing.txt")
        except:
            pass
        print("Let's Start...")
    elif content.decode() == '"END"':
        image_object.flag = False
        print(str(image_object.image_bytes))
        image_path = ''
        try:
            byte_stream = io.BytesIO(image_object.image_bytes)
            ImageFile.LOAD_TRUNCATED_IMAGES = True
            im = Image.open(byte_stream)
            im.save("./static/img/testing.png")
            im = cv2.imread("./static/img/testing.png")
            image_path = "./static/img/testing.png"

            im = white_balance_2(im)
            cv2.imwrite("./static/img/balanced_2.png", np.vstack([im]))
            im = white_balance_3(im)
            cv2.imwrite("./static/img/balanced_3.png", np.vstack([im]))
            im = white_balance_4(im)
            cv2.imwrite("./static/img/balanced_4.png", np.vstack([im]))
            # im = white_balance_5(im)
            # cv2.imwrite("./static/img/balanced_5.png", np.vstack([im])) 
            print('Finished Used ', time.time()-image_object.start, "s")
        except:
            print('Backup')
            image_path = "./static/img/backup.png" 

        print("Start Trash Idenitifcation: ")

        image_object.image_bytes = b''
        # import tensorflow as tf
        import sys
        import os

        # Disable tensorflow compilation warnings
        os.environ['TF_CPP_MIN_LOG_LEVEL'] = '2'
        # import tensorflow as tf
        import tensorflow.compat.v1 as tf

        

        if image_path:

            # Read the image_data
            image_data = tf.gfile.FastGFile(image_path, 'rb').read()

            # Loads label file, strips off carriage return
            label_lines = [line.rstrip() for line
                           in tf.gfile.GFile("./static/tf_files/retrained_labels.txt")]

            # Unpersists graph from file
            with tf.gfile.FastGFile("./static/tf_files/retrained_graph.pb", 'rb') as f:
                graph_def = tf.GraphDef()
                graph_def.ParseFromString(f.read())
                _ = tf.import_graph_def(graph_def, name='')

            with tf.Session() as sess:
                # Feed the image_data as input to the graph and get first prediction
                softmax_tensor = sess.graph.get_tensor_by_name('final_result:0')

                predictions = sess.run(softmax_tensor, \
                                       {'DecodeJpeg/contents:0': image_data})

                # Sort to show labels of first prediction in order of confidence
                top_k = predictions[0].argsort()[-len(predictions[0]):][::-1]


                for node_id in top_k:
                    human_string = label_lines[node_id]
                    score = predictions[0][node_id]

                    print('%s (score = %.5f)' % (human_string, score))
                    response += '%s (score = %.5f)\n' % (human_string, score)


    else:
        f = open("./static/img/testing.txt", 'a')
        for each in content.decode().split('zz'):
            if len(each):
                # print('each: ', each, type(each))
                f.write(each + '\n')
                exec("allocate=" + each, globals(), globals())
                image_object.image_bytes += allocate
        # print(image_object.image_bytes)
        print('Pass ', time.time()-image_object.start, "s")
        f.close()
    
    print("Successful Analyzed!")
    return HttpResponse(response)


@csrf_exempt
def recommend(request):

    context = {}
    context['content'] = request.method

    print('Enter to Recommend Page')
    # print(request.body)
    # print(type(request.body))

    response = ''

    if request.method == 'POST' and request.FILES:
        file_name = list(request.FILES.keys())[0]
        myfile = request.FILES[file_name]
        print("File name: ", myfile)
        print("File type: ", type(myfile))

        im = Image.open(myfile)
        im.save("./static/img/testing.png")
        print('Saved Upload Picture')

        # import tensorflow as tf
        import sys
        import os

        # Disable tensorflow compilation warnings
        os.environ['TF_CPP_MIN_LOG_LEVEL'] = '2'
        # import tensorflow as tf
        import tensorflow.compat.v1 as tf

        image_path = "./static/img/testing.png"

        if image_path:

            # Read the image_data
            image_data = tf.gfile.FastGFile(image_path, 'rb').read()

            # Loads label file, strips off carriage return
            label_lines = [line.rstrip() for line
                           in tf.gfile.GFile("./static/tf_files/retrained_labels.txt")]

            # Unpersists graph from file
            with tf.gfile.FastGFile("./static/tf_files/retrained_graph.pb", 'rb') as f:
                graph_def = tf.GraphDef()
                graph_def.ParseFromString(f.read())
                _ = tf.import_graph_def(graph_def, name='')

            with tf.Session() as sess:
                # Feed the image_data as input to the graph and get first prediction
                softmax_tensor = sess.graph.get_tensor_by_name('final_result:0')

                predictions = sess.run(softmax_tensor, \
                                       {'DecodeJpeg/contents:0': image_data})

                # Sort to show labels of first prediction in order of confidence
                top_k = predictions[0].argsort()[-len(predictions[0]):][::-1]


                for node_id in top_k:
                    human_string = label_lines[node_id]
                    score = predictions[0][node_id]

                    print('%s (score = %.5f)' % (human_string, score))
                    response += '%s (score = %.5f)\n' % (human_string, score)


    print("Successful Analyzed!")
    return HttpResponse(response)

def seepic(request):
    context = {}
    context['content1'] = 'Hello World'
    # import tensorflow as tf
    import sys
    import os

    # Disable tensorflow compilation warnings
    os.environ['TF_CPP_MIN_LOG_LEVEL'] = '2'
    # import tensorflow as tf
    import tensorflow.compat.v1 as tf

    image_path = "./static/img/testing.png"

    response = ''

    if image_path:

        # Read the image_data
        image_data = tf.gfile.FastGFile(image_path, 'rb').read()

        # Loads label file, strips off carriage return
        label_lines = [line.rstrip() for line
                        in tf.gfile.GFile("./static/tf_files/retrained_labels.txt")]

        # Unpersists graph from file
        with tf.gfile.FastGFile("./static/tf_files/retrained_graph.pb", 'rb') as f:
            graph_def = tf.GraphDef()
            graph_def.ParseFromString(f.read())
            _ = tf.import_graph_def(graph_def, name='')

        with tf.Session() as sess:
            # Feed the image_data as input to the graph and get first prediction
            softmax_tensor = sess.graph.get_tensor_by_name('final_result:0')

            predictions = sess.run(softmax_tensor, \
                                    {'DecodeJpeg/contents:0': image_data})

            # Sort to show labels of first prediction in order of confidence
            top_k = predictions[0].argsort()[-len(predictions[0]):][::-1]


            for node_id in top_k:
                human_string = label_lines[node_id]
                score = predictions[0][node_id]

                print('%s (score = %.5f)' % (human_string, score))
                response += '%s (score = %.5f)\n' % (human_string, score)


    print("Successful Analyzed!")
    return HttpResponse(response)
