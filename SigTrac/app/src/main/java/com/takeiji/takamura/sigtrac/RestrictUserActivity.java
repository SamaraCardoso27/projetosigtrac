package com.takeiji.takamura.sigtrac;

import android.Manifest;
import android.app.AlertDialog;
import android.content.Context;
import android.content.DialogInterface;
import android.content.Intent;
import android.content.pm.PackageManager;
import android.location.Location;
import android.location.LocationListener;
import android.location.LocationManager;
import android.support.v4.app.ActivityCompat;
import android.support.v4.content.ContextCompat;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.telephony.TelephonyManager;
import android.util.Log;
import android.view.View;
import android.widget.TextView;
import android.widget.Toast;

import org.w3c.dom.Text;

import java.util.ArrayList;
import java.util.List;

public class RestrictUserActivity extends AppCompatActivity {

    private String CPF;
    private String Name;

    private TextView mTitle;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_restrict_user);
        getSupportActionBar().hide();

        // Getting the name and CPF
        Intent intent = getIntent();
        CPF = intent.getStringExtra("CPF");
        Name = intent.getStringExtra("NOME");

        // Loading UI elements
        mTitle = (TextView) findViewById(R.id.title_restrictedUsers);

        // Setting welcome text
        mTitle.setText("Bem-vindo " + this.Name);
    }

    // It sends the CPF, phone number, position and a flag (restricted user/common user)
    public void emitAlertSignal(View view) {
        AlertDialog.Builder builder = new AlertDialog.Builder(this);
        builder.setMessage("Deseja enviar sinal de pânico?").setTitle("Emergencia");
        builder.setPositiveButton("Sim", new DialogInterface.OnClickListener() {
            @Override
            public void onClick(DialogInterface dialog, int which) {
                Location location = getLocation();
                SinalDePanico sinal = new SinalDePanico(getApplicationContext(), CPF, location, true);
                sinal.enviar();
            }
        });
        builder.setNegativeButton("Nao", new DialogInterface.OnClickListener() {
            @Override
            public void onClick(DialogInterface dialog, int which) {

            }
        });
        AlertDialog dialog = builder.create();
        dialog.show();
    }


    public void verificarAlertas(View view) {
        // TODO: Abrir uma nova tela, requerir os alertas da central, mostrar eles
    }

    public void enviarAlerta(View view) {
        Intent intent = new Intent(this, SendAlertActivity.class);
        startActivity(intent);
    }

    private Location getLocation() {

        LocationListener locationListener = null;
        Location currentLocation = null;

        try {
            Context context = getApplicationContext();

            if(ContextCompat.checkSelfPermission(context, Manifest.permission.ACCESS_FINE_LOCATION) == PackageManager.PERMISSION_GRANTED) {
                LocationManager locationManager = (LocationManager) context.getSystemService(Context.LOCATION_SERVICE);

                locationListener = new AlertaLocationListener(context);
                locationManager.requestLocationUpdates(LocationManager.GPS_PROVIDER, 0, 0, locationListener);

                currentLocation = locationManager.getLastKnownLocation(LocationManager.GPS_PROVIDER);
            }
        } catch (Exception ex) {
            Toast.makeText(getApplicationContext(), "Serviço GPS indisponivel", Toast.LENGTH_SHORT).show();
        }

        if(currentLocation == null) {
            Toast.makeText(getApplicationContext(), "Serviço GPS indisponivel", Toast.LENGTH_SHORT);
        }
        return currentLocation;
    }
}
