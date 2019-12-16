package com.example.smarttrashbin;

import android.Manifest;
import android.content.Intent;
import android.content.pm.PackageManager;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.icu.text.SimpleDateFormat;
import android.net.Uri;
import android.os.Bundle;
import android.os.Environment;
import android.provider.MediaStore;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.ImageView;
import android.widget.TextView;
import android.widget.Toast;

import com.anychart.anychart.AnyChart;
import com.anychart.anychart.AnyChartView;
import com.anychart.anychart.DataEntry;
import com.anychart.anychart.Pie;
import com.anychart.anychart.ValueDataEntry;

import org.apache.http.HttpEntity;
import org.apache.http.HttpResponse;
import org.apache.http.client.HttpClient;
import org.apache.http.client.methods.HttpGet;
import org.apache.http.client.methods.HttpPost;
import org.apache.http.entity.mime.HttpMultipartMode;
import org.apache.http.entity.mime.MultipartEntity;
import org.apache.http.entity.mime.content.ContentBody;
import org.apache.http.entity.mime.content.FileBody;
import org.apache.http.entity.mime.content.StringBody;
import org.apache.http.impl.client.DefaultHttpClient;
import org.apache.http.util.EntityUtils;
import org.w3c.dom.Text;

import java.io.ByteArrayOutputStream;
import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.net.URI;
import java.util.ArrayList;
import java.util.Date;
import java.util.List;
import java.util.Locale;

import androidx.annotation.NonNull;
import androidx.appcompat.app.AppCompatActivity;
import androidx.core.app.ActivityCompat;
import androidx.core.content.ContextCompat;
import androidx.core.content.FileProvider;

public class MainActivity extends AppCompatActivity {

    private Button cameraBtn;
    private ImageView imageView;
    //edit for uploading
    private Button uploadBtn;
    private TextView trashTypeView;

    private Button requestBtn;

    private EditText positionText;

    public static final int REQUEST_IMAGE = 100;
    public static final int REQUEST_PERMISSION = 200;
    private String imageFilePath = "";

    private Button layout1Btn;
    private Button layout2Btn;

    private Button return1Btn;
    private Button return2Btn;

    private TextView typeView;



    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        changMainLayoutIntent();
    }
    //click camera -> create a photo file, then store snapshot into it

    private void changMainLayoutIntent(){
        setContentView(R.layout.main_activity);

        layout1Btn = findViewById(R.id.layout1Btn);
        layout2Btn = findViewById(R.id.layout2Btn);

        layout1Btn.setOnClickListener(new View.OnClickListener(){
            @Override
            public void onClick(View view) {
                changeLayout1Intent();
            }
        });
        layout2Btn.setOnClickListener(new View.OnClickListener(){
            @Override
            public void onClick(View view) {
                changeLayout2Intent();
            }
        });
    }

    private void changeLayout1Intent(){
        setContentView(R.layout.take_photo);
        cameraBtn = findViewById(R.id.cameraBtn);
        imageView = findViewById(R.id.imagePreview);
        //edit for uploading
        uploadBtn = findViewById(R.id.uploadBtn);
        return1Btn = findViewById(R.id.return1Btn);
        typeView = findViewById(R.id.typeView);

        if (ContextCompat.checkSelfPermission(this, Manifest.permission.WRITE_EXTERNAL_STORAGE) !=
                PackageManager.PERMISSION_GRANTED) {
            ActivityCompat.requestPermissions(this, new String[] {Manifest.permission.WRITE_EXTERNAL_STORAGE},
                    REQUEST_PERMISSION);
        }

        cameraBtn.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                openCameraIntent();
            }
        });

        //edit for uploading
        uploadBtn.setOnClickListener(new View.OnClickListener(){
            @Override
            public void onClick(View view) {
                uploadImageIntent();
            }
        });

        return1Btn.setOnClickListener(new View.OnClickListener(){
            @Override
            public void onClick(View view) {
                changMainLayoutIntent();
            }
        });
    };

    private void changeLayout2Intent(){
        setContentView(R.layout.call_and_show);
        requestBtn = findViewById(R.id.requestBtn);
        positionText = findViewById(R.id.positionText);
        return2Btn = findViewById(R.id.return2Btn);

        requestBtn.setOnClickListener(new View.OnClickListener(){
            @Override
            public void onClick(View view) {
                callTrashBinIntent();
            }
        });

        return2Btn.setOnClickListener(new View.OnClickListener(){
            @Override
            public void onClick(View view) {
                changMainLayoutIntent();
            }
        });
    };


    private void openCameraIntent() {
        Intent pictureIntent = new Intent(MediaStore.ACTION_IMAGE_CAPTURE);
        if (pictureIntent.resolveActivity(getPackageManager()) != null) {

            File photoFile = null;
            try {
                photoFile = createImageFile();
            }
            catch (IOException e) {
                e.printStackTrace();
                return;
            }
            Uri photoUri = FileProvider.getUriForFile(this, getPackageName() +".provider", photoFile);
            pictureIntent.putExtra(MediaStore.EXTRA_OUTPUT, photoUri);
            startActivityForResult(pictureIntent, REQUEST_IMAGE);
        }
    }

    private void uploadImageIntent(){
        Thread thread = new Thread(new Runnable(){
            public void run() {
                try {
                    HttpClient httpclient = new DefaultHttpClient();
//        httpclient.getParams().setParameter(CoreProtocolPNames.PROTOCOL_VERSION, HttpVersion.HTTP_1_1);
                    HttpPost httppost = new HttpPost("http://6155cfaa.ngrok.io/recommend");
//                    HttpPost httppost = new HttpPost("http://2fa10552.ngrok.io/recommend");
                    File file = new File(imageFilePath);
                    MultipartEntity mpEntity = new MultipartEntity(HttpMultipartMode.BROWSER_COMPATIBLE);
//        ContentBody cbFile = new FileBody(file, "image/jpeg");
                    Log.e("print","below are compressing");
                    Bitmap original = BitmapFactory.decodeFile(file.getPath());
                    ByteArrayOutputStream out = new ByteArrayOutputStream();
                    original.compress(Bitmap.CompressFormat.JPEG, 50, out);
//                    Bitmap decoded = BitmapFactory.decodeStream(new ByteArrayInputStream(out.toByteArray()));
                    File f = null;
                    f = createCompressedImageFile();
                    f.createNewFile();
                    FileOutputStream fos = new FileOutputStream(f);
                    fos.write(out.toByteArray());
                    fos.flush();
                    fos.close();

                    ContentBody cbFile = new FileBody(f);
                    mpEntity.addPart("Filename", new StringBody(f.getName()));
                    mpEntity.addPart("Filedata", cbFile);


                    httppost.setEntity(mpEntity);
                    Log.e("step", "executing request " + httppost.getRequestLine());
                    HttpResponse response = httpclient.execute(httppost);
                    HttpEntity resEntity = response.getEntity();

                    Log.e("step", response.getStatusLine().toString());
                    if (resEntity != null) {
                        final String result_str = EntityUtils.toString(resEntity);
                        typeView.setText(result_str);
                        Log.e("step-result", result_str);
                    }
                    if (resEntity != null) {
                        resEntity.consumeContent();
                    }

                    httpclient.getConnectionManager().shutdown();
                } catch (Exception e) {
                    e.printStackTrace();
                    Log.e("error",imageFilePath);
                }
            }
        });

        thread.start();
    }

    private void callTrashBinIntent(){

        Thread thread = new Thread(new Runnable(){
            public void run() {
                try {
                    trashTypeView = findViewById(R.id.trashTypeView);
                    String position_str = positionText.getText().toString();
                    if (position_str != null) {
                        HttpClient httpclient = new DefaultHttpClient();
                        URI uri = new URI("https://6155cfaa.ngrok.io/acceptCommand?Command=action:" + position_str);
//                        URI uri = new URI("http://466bdb4c.ngrok.io?Command=action:" + position_str);
                        HttpGet httpget = new HttpGet(uri);
                        HttpResponse response = httpclient.execute(httpget);
                        HttpEntity resEntity = response.getEntity();
                        if (resEntity != null) {
                            final String result_str = EntityUtils.toString(resEntity);
                            Log.e("step-result", result_str);
                            trashTypeView.setText(result_str);

                        }
                        if (resEntity != null) {
                            resEntity.consumeContent();
                        }

                        httpclient.getConnectionManager().shutdown();
//                        String response_code = response.toString().split(" ")[1];
//                        if (response_code == "404")
//                            trashTypeView.setText("Oops. We can't get it.");
//                        else if (response_code == "200")
//                        trashTypeView.setText(response.toString());
                    }
                    else{

                    }
                } catch (Exception e) {
                    e.printStackTrace();
                }
            }});
        thread.start();
    }


    @Override
    public void onRequestPermissionsResult(int requestCode, @NonNull String[] permissions, @NonNull int[] grantResults) {
        super.onRequestPermissionsResult(requestCode, permissions, grantResults);

        if (requestCode == REQUEST_PERMISSION && grantResults.length > 0) {
            if (grantResults[0] == PackageManager.PERMISSION_GRANTED) {
                Toast.makeText(this, "Thanks for granting Permission", Toast.LENGTH_SHORT).show();
            }
        }
    }

    @Override
    protected void onActivityResult(int requestCode, int resultCode, Intent data) {
        super.onActivityResult(requestCode, resultCode, data);

        if (requestCode == REQUEST_IMAGE) {
            if (resultCode == RESULT_OK) {
                imageView.setImageURI(Uri.parse(imageFilePath));
            }
            else if (resultCode == RESULT_CANCELED) {
                Toast.makeText(this, "You cancelled the operation", Toast.LENGTH_SHORT).show();
            }
        }
    }

    private File createImageFile() throws IOException{

        String timeStamp = new SimpleDateFormat("yyyyMMdd_HHmmss", Locale.getDefault()).format(new Date());
        String imageFileName = "IMG_" + timeStamp + "_";
        File storageDir = getExternalFilesDir(Environment.DIRECTORY_PICTURES);
        File image = File.createTempFile(imageFileName, ".jpg", storageDir);
        imageFilePath = image.getAbsolutePath();
        Log.e("print",imageFilePath);
        return image;
    }

    private File createCompressedImageFile() throws IOException{

        String timeStamp = new SimpleDateFormat("yyyyMMdd_HHmmss", Locale.getDefault()).format(new Date());
        String imageFileName = "IMG_" + timeStamp + "_";
        File storageDir = getExternalFilesDir(Environment.DIRECTORY_PICTURES);
        File image = File.createTempFile(imageFileName, ".jpg", storageDir);
        imageFilePath = image.getAbsolutePath();
        Log.e("print",imageFilePath);
        return image;
    }

}
