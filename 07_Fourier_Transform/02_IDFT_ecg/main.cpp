#include <iostream>
#include <cmath>
#include <fstream>

#define SIG_LENGTH 640
using namespace std;

extern double _640_points_ecg_[640];

  double Output_REX[SIG_LENGTH];
 double Output_IMX[SIG_LENGTH];
double Output_MAG[SIG_LENGTH];
double Output_IDFT[SIG_LENGTH];

void calc_sig_dft( double *sig_src_arr,double *sig_dest_rex_arr,double  *sig_dest_imx_arr,int sig_length);
void get_dft_output_mag(double * sig_dest_mag_arr, double * sig_src_rex_arr, double * sig_src_imx_arr );
void calc_idft(double *idft_out_arr, double *sig_src_rex_arr,double *sig_src_imx_arr, int idft_length);


int main()
{
     ofstream file1,file2,file3,file4,file5;

     calc_sig_dft( (double *)&_640_points_ecg_[0],
                   (double *)&Output_REX[0],
                   (double *)&Output_IMX[0],
                   (int) SIG_LENGTH
                  );

     get_dft_output_mag((double *)&Output_MAG[0], (double *)&Output_REX[0], (double *) &Output_IMX[0] );

      calc_idft((double *)&Output_IDFT[0], (double *)&Output_REX[0],(double *)&Output_IMX[0], (int) SIG_LENGTH);


     file1.open("input_signal.dat");
     file2.open("output_rex.dat");
     file3.open("output_imx.dat");
     file4.open("output_mag.dat");
     file5.open("output_idft.dat");

     for(int i=0;i<SIG_LENGTH;i++){
        file1<<_640_points_ecg_[i]<<endl;

        file2<<Output_REX[i]<<endl;
        file3<<Output_IMX[i]<<endl;
        file4<<Output_MAG[i]<<endl;

        file5<<Output_IDFT[i]<<endl;


     }

    file1.close();
    file2.close();
    file3.close();
    file4.close();
    file5.close();

    return 0;
}


void calc_sig_dft( double *sig_src_arr,
                   double *sig_dest_rex_arr,
                   double  *sig_dest_imx_arr,
                   int sig_length
                  )
{
	int j,k,i;

	for(j=0;j<sig_length;j++)
	{
	  sig_dest_imx_arr[j] =0;
		sig_dest_rex_arr[j] =0;
	}

	for(k=0;k<sig_length;k++)
	{
	   for(i=0;i<sig_length;i++)
		 {
		     sig_dest_rex_arr[k] =  sig_dest_rex_arr[k] + sig_src_arr[i]*cos(2*M_PI*k*i/sig_length);
				 sig_dest_imx_arr[k] =  sig_dest_imx_arr[k] - sig_src_arr[i]*sin(2*M_PI*k*i/sig_length);
     }
	}
}


void get_dft_output_mag(double * sig_dest_mag_arr, double * sig_src_rex_arr, double * sig_src_imx_arr )
{
    int x;
    for(x =0;x<SIG_LENGTH/2;x++){
        sig_dest_mag_arr[x]  = sqrt(pow(sig_src_rex_arr[x],2)+ pow(sig_src_imx_arr[x],2));
    }

}


void calc_idft(double *idft_out_arr, double *sig_src_rex_arr,double *sig_src_imx_arr, int idft_length)
{

int i,k;

    for(k=0;k<idft_length;k++){

         sig_src_rex_arr[k] =  sig_src_rex_arr[k]/(idft_length/2);
         sig_src_imx_arr[k] =  sig_src_imx_arr[k]/(idft_length/2);
    }

     for(k =0;k<idft_length;k++){
        idft_out_arr[k] = 0;
     }

     for(k =0;k<idft_length/2;k++){

        for(i =0;i<idft_length;i++){

            idft_out_arr[i] = idft_out_arr[i] +  sig_src_rex_arr[k]* cos(2*M_PI*k*i/idft_length);
            idft_out_arr[i] =  idft_out_arr[i] + sig_src_imx_arr[k]* sin(2*M_PI*k*i/idft_length);
        }
     }
}


