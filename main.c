#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <unistd.h>
#include <fcntl.h>

/*
  * Format: ./main -s <seconds> -i <interface>
  *
*/


int main(int argc, char *argv[])
{
  /* if (argc < 4){ */
  /*   printf("Error usage\n"); */
  /*   return -1; */
  /**/
  /* } */

  char *network_interface = argv[4];
  int seconds_to_sleep = atoi(argv[2]);
  char rx_path[128];
  char tx_path[128];

  /* char *final =  "/sys/class/net/" + *network_interface + "/statistics/rx_bytes"; */
  // fixed:
  snprintf(rx_path, sizeof(rx_path), "/sys/class/net/%s/statistics/rx_bytes", network_interface);
  snprintf(tx_path, sizeof(tx_path), "/sys/class/net/%s/statistics/tx_bytes", network_interface);


  // could not find a way to refresh buffer using:
  /* FILE *rx_file_ptr; */
  /* FILE *tx_file_ptr; */
  /**/
  /* rx_file_ptr = fopen(rx_path, "r"); */
  /* tx_file_ptr = fopen(tx_path, "r"); */
  /* fclose(rx_file_ptr); */
  /* fclose(tx_file_ptr); */



  // used this to implement refresh
  int tx_f = open(tx_path, O_RDONLY);
  int rx_f = open(rx_path, O_RDONLY);

  char tx_data[32]; // max size: 20 decimal places + null terminator char (21)
  char tx_data_after[32]; // max size: 20 decimal places + null terminator char (21)
  char rx_data[32]; 
  char rx_data_after[32]; 
  
  while (1){

    ssize_t tx_len = pread(tx_f, tx_data, sizeof(tx_data) - 1, 0);
    ssize_t rx_len = pread(rx_f, rx_data, sizeof(rx_data) - 1, 0);
    tx_data[tx_len - 1] = '\0';
    rx_data[rx_len - 1] = '\0';

    int tx_bytes_int = atoi(tx_data);
    int tx_kbs = tx_bytes_int / 1024;
    int tx_mb = tx_kbs / 1024;
    int rx_bytes_int = atoi(rx_data);
    int rx_kbs = rx_bytes_int / 1024;
    int rx_mb = rx_kbs / 1024;


    /* printf("\rTotal ↑: %s | Total ↓: %s", tx_data, rx_data); */ // str
    /* printf("\rTotal ↑: %d | Total ↓: %d", tx_kbs, rx_kbs); */
    fflush(stdout);
    sleep(seconds_to_sleep);

    ssize_t tx_len_after = pread(tx_f, tx_data_after, sizeof(tx_data_after) - 1, 0);
    tx_data_after[tx_len_after - 1] = '\0';
    int results = atoi(tx_data_after) - tx_bytes_int;

    ssize_t rx_len_after = pread(rx_f, rx_data_after, sizeof(rx_data_after) - 1, 0);
    tx_data_after[tx_len_after - 1] = '\0';
    int results = atoi(tx_data_after) - tx_bytes_int;
    /* printf("\rTotal ↑: %d | Total ↓: %d", tx_kbs, rx_kbs); */
  }



  close(tx_f);
  close(rx_f);

  return 0;
}

