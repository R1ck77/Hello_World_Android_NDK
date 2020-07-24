package it.couchgamessoftware.helloworld.metal;

import androidx.appcompat.app.AppCompatActivity;

import android.content.res.AssetManager;
import android.os.Bundle;
import android.os.Environment;
import android.util.Log;
import android.widget.TextView;

import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;

public class MainActivity extends AppCompatActivity {

    // Used to load the 'native-lib' library on application startup.
    static {
        System.loadLibrary("native-lib");
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        //checkAssets();
        copyAssets();
        listExternalStorage();

        // Example of a call to a native method
        TextView tv = findViewById(R.id.sample_text);
        tv.setText(stringFromJNI(getExternalCacheDir().getAbsolutePath()));
    }

    private void listExternalStorage() {
        File sd_path = getExternalCacheDir();
        for(String name: sd_path.list()) {
            Log.d("HelloWorldNDK", "Found external file: " + name);
        }
    }

    private void copyAssets() {
        File guardFile = new File(getExternalCacheDir() + "/libraries_copied.guard");
        if(!guardFile.exists()) {
            try {
                copyDirOrFileFromAssetManager("arm64-v8a", "arm64-v8a");
                copyDirOrFileFromAssetManager("armeabi-v7a", "armeabi-v7a");
                guardFile.createNewFile();
            } catch (IOException e) {
                Log.e("HelloWorldNDK", "===== Exception: " + e);
                e.printStackTrace();
            }
        } else {
            Log.d("HelloWorldNDK", "===== File copy not required =)");
        }
    }

    private void checkAssets() {
        AssetManager assets = getAssets();
        Log.i("HelloWorldNDK", "======== About to list the assets!");
        try {
            for(String path: assets.list("")) {
                Log.i("HelloWorldNDK", "******* Found: " + path);
            }
            Log.i("HelloWorldNDK", "======== Assets listed...");
        } catch (IOException e) {
            Log.d("HelloWorldNDK", "Exception " + e);
            e.printStackTrace();
        }
    }


    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     * @param absolutePath
     */
    public native String stringFromJNI(String absolutePath);



    public String copyDirOrFileFromAssetManager(String arg_assetDir, String arg_destinationDir) throws IOException
    {
        File sd_path = getExternalCacheDir();
        String dest_dir_path = sd_path + addLeadingSlash(arg_destinationDir);
        File dest_dir = new File(dest_dir_path);

        createDir(dest_dir);

        AssetManager asset_manager = getApplicationContext().getAssets();
        String[] files = asset_manager.list(arg_assetDir);

        for (int i = 0; i < files.length; i++)
        {

            String abs_asset_file_path = addTrailingSlash(arg_assetDir) + files[i];
            String sub_files[] = asset_manager.list(abs_asset_file_path);

            if (sub_files.length == 0)
            {
                // It is a file
                String dest_file_path = addTrailingSlash(dest_dir_path) + files[i];
                copyAssetFile(abs_asset_file_path, dest_file_path);
            } else
            {
                // It is a sub directory
                copyDirOrFileFromAssetManager(abs_asset_file_path, addTrailingSlash(arg_destinationDir) + files[i]);
            }
        }

        return dest_dir_path;
    }


    public void copyAssetFile(String assetFilePath, String destinationFilePath) throws IOException
    {
        InputStream in = getApplicationContext().getAssets().open(assetFilePath);
        OutputStream out = new FileOutputStream(destinationFilePath);

        byte[] buf = new byte[1024];
        int len;
        while ((len = in.read(buf)) > 0)
            out.write(buf, 0, len);
        in.close();
        out.close();
    }

    public String addTrailingSlash(String path)
    {
        if (path.charAt(path.length() - 1) != '/')
        {
            path += "/";
        }
        return path;
    }

    public String addLeadingSlash(String path)
    {
        if (path.charAt(0) != '/')
        {
            path = "/" + path;
        }
        return path;
    }

    public void createDir(File dir) throws IOException
    {
        if (dir.exists())
        {
            if (!dir.isDirectory())
            {
                throw new IOException("Can't create directory, a file is in the way");
            }
        } else
        {
            dir.mkdirs();
            if (!dir.isDirectory())
            {
                throw new IOException("Unable to create directory");
            }
        }
    }

}
