// DLL version of Injector by Sam Nazarko - 3/01/2010
// Based on Injector.exe by Scott Davilla
// Adapted for DllImport in atv-win-3.0
// C includes
#include  <stdlib.h>
#include  <stdio.h>
#include   <string.h>

#ifdef WIN32
  #include   <Windows.h>
  #include  <tchar.h>
  #include  <signal.h>
  #define CGetTickCount GetTickCount
  double CGetTime();
  double CGetTime() {
    // return time in seconds since midnight (0 hour), January 1, 1970.
    //struct timeval      tp;
    //double          cur_seconds;

    //gettimeofday(&tp, NULL);
    //cur_seconds = (double)tp.tv_sec + (1e-6 * tp.tv_usec);

    return( GetTickCount() );
  }
  char* 
  strcasestr(const char *s, const char *find);
  char* 
  strcasestr(const char *s, const char *find) 
  { 
        char c, sc; 
        size_t len; 

        if ((c = *find++) != 0) { 
                c = tolower((unsigned char)c); 
                len = strlen(find); 
                do { 
                        do { 
                                if ((sc = *s++) == 0) 
                                        return (NULL); 
                        } while ((char)tolower((unsigned char)sc) != c); 
                } while (_strnicmp(s, find, len) != 0); 
                s--; 
        } 
        return ((char *)s); 

  } 
  #pragma comment(lib, "ws2_32") 
#else
  #include  <unistd.h>
  double CGetTime();
  double CGetTime() {
    // return time in seconds since midnight (0 hour), January 1, 1970.
    struct timeval      tp;
    double          cur_seconds;

    gettimeofday(&tp, NULL);

    cur_seconds = (double)tp.tv_sec + (1e-6 * tp.tv_usec);
    return(cur_seconds);
  }
#endif
void  signal_control_c(int value);
void  millisecond_sleep(int milliseconds);
bool  parse_int_argv(char *argv, char *param_str, int *param);
bool  parse_str_argv(char *argv, char *param_str, char *param);
void signal_control_c(int value)
{
  // when the signal handler is called, the signal handler for 
  //  that particular signal is reset to the default handler
  // so to keep getting these signals we need to reset signal handler within itself
  //signal(SIGINT, signal_control_c);
  printf("\nAbort    :\n");
  fflush(stdout);
}
void  millisecond_sleep(int milliseconds)
{
  timeval    t;
  
  t.tv_sec = milliseconds / 1000;
  t.tv_usec = (milliseconds % 1000 ) *1000;
  select(0, NULL, NULL, NULL, &t);
}
bool  parse_int_argv(char *argv, char *param_str, int *param)
{
  char    *str_ptr;
  
  str_ptr = strcasestr(argv, param_str);
  
  if (str_ptr) {
    str_ptr = strcasestr(argv, "=");
    if (str_ptr) {
      str_ptr++;
    
      *param = atoi(str_ptr);
    }
  }
    
  return(str_ptr != NULL);
}
bool  parse_str_argv(char *argv, char *param_str, char *param)
{
  char    *str_ptr;
  
  str_ptr = strcasestr(argv, param_str);
  
  if (str_ptr) {
    str_ptr = strcasestr(argv, "=");
    if (str_ptr) {
      str_ptr++;
    
      strcpy(param, str_ptr);
    }
  }
    
  return(str_ptr != NULL);
}

#ifdef WIN32
  int _tmain(int argc, _TCHAR* argv[]);
#else
  int main(int argc, char *argv[]);
#endif
//atv-win mod
//injector is now an exposed DLL.
extern "C"
{
	_declspec(dllexport) int newefi() {

  int                     i, io_status;
  bool                    show_progress;
  char                    io_basename[1024];
  int                     io_baseoffset;
  size_t                  io_basesize;
  char                    io_filename[1024];
  int                     io_fileoffset;
  size_t                  io_filesize;

  char                    *buffer;
  FILE                    *in_file, *out_file;
  size_t                  in_len, out_len,read_size;
  size_t                  bytes_copied;
  // defaults for atv-win
  io_status = 0;
  bytes_copied = 0;
  show_progress = false;
  strcpy(io_basename, "ImageFile.img");
  io_baseoffset = 2437120;
  strcpy(io_filename, "boot.efi");
  io_fileoffset = 0;
  in_file = fopen(io_filename, "rb");
  if (!in_file) {
    return(-1);
  }
  // get the file size in bytes
  fseek(in_file, 0, SEEK_END);
  io_filesize = ftell(in_file);
  // rewind back to start
  fseek(in_file, 0, SEEK_SET);
  out_file = fopen(io_basename, "rb+");
  if (!out_file) {
    fclose(in_file);
    return(-3);
  }
  // get the file size in bytes
  fseek(out_file, 0, SEEK_END);
  io_basesize = ftell(out_file);
  // rewind back to start
  fseek(out_file, 0, SEEK_SET);
  // check that ending point does not extend past size of disk image
  if (io_filesize > (io_basesize - io_baseoffset) ) {
    io_filesize = io_basesize - io_baseoffset;
  }
  // setup for 512k chunks
  read_size = 512 * 1024 * 1024;
  if (io_filesize < read_size) {
      read_size = io_filesize;
  }
  //read_size = 4096;
  buffer = (char*)malloc(read_size);
  // seek to inject point
  fseek(out_file, io_baseoffset, SEEK_SET);
  // inject the input file to the base file
  size_t tmp_int;
  do {
	tmp_int = ftell(in_file);
    in_len = fread(buffer, 1, read_size, in_file);
    if (in_len > 0) {
      out_len = fwrite(buffer, 1, in_len, out_file);
	  fflush(out_file);
      // and keep track of data written
      if (out_len > 0) bytes_copied += out_len;
      io_status = (int)(100.0 * (float)bytes_copied / (float)io_filesize);
    }


  } while (in_len);
  // Close the files
  fclose(in_file);                  
  fclose(out_file);
	}
}


