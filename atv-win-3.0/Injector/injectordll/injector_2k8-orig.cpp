// C includes
#include  <stdlib.h>
#include  <stdio.h>
#include   <string.h>

#ifdef WIN32
  #include   <Windows.h>
  #include  <tchar.h>
  #include  <signal.h>
  //_____________________________________________________________________________
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

  //_____________________________________________________________________________
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

//________________________________________________________________________________
//________________________________________________________________________________
//________________________________________________________________________________
#ifdef WIN32
  int _tmain(int argc, _TCHAR* argv[])
#else
  int main(int argc, char *argv[])
#endif
{
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

  //__________________________________________________________
  // defaults
  io_status = 0;
  bytes_copied = 0;
  show_progress = false;
  strcpy(io_basename, "");
  io_baseoffset = 0;
  strcpy(io_filename, "");
  io_fileoffset = 0;

  //__________________________________________________________
  // Trap control C, close ups stuff then exit
  signal(SIGINT, signal_control_c);  

  //__________________________________________________________
  //__________________________________________________________
  // Check command line arguments
  // argv[0] is application path so we really get n+1 for argc
  for (i = 1; i < argc; i++) {
    int        tmp_int = 0;
    
    if ( strstr(argv[i], "--basefile=") ) {
      char      tmp_basepath[1024];
      
      strcpy(tmp_basepath, "");
      if ( parse_str_argv(argv[i], "--basefile=", tmp_basepath) ) {
        if (strlen(tmp_basepath) ) {
          strcpy(io_basename, tmp_basepath);
        } else {
          fprintf(stderr, "argument error %s\n", argv[i]);
          return(-1);
        }
      } 
      //
    } else if ( strstr(argv[i], "--baseseek=") ) {
      if ( parse_int_argv(argv[i], "--baseseek=", &tmp_int) ) {
        if ( tmp_int >= 0 ) {
          io_baseoffset = tmp_int;
        } else {
          fprintf(stderr, "argument error %s\n", argv[i]);
          return(-1);
        }
      } 
      //
    } else if ( strstr(argv[i], "--infile=") ) {
      char      tmp_filepath[1024];
      
      strcpy(tmp_filepath, "");
      if ( parse_str_argv(argv[i], "--infile=", tmp_filepath) ) {
        if (strlen(tmp_filepath) ) {
          strcpy(io_filename, tmp_filepath);
        } else {
          fprintf(stderr, "argument error %s\n", argv[i]);
          return(-1);
        }
      } 
      //
    } else if ( strstr(argv[i], "--show-progress") ) {
      show_progress = true;
      //
    } else if ( strstr(argv[i], "--help") ) {
      fprintf(stderr, "A command line tool for the injection of a file into a disk image\n");
      fprintf(stderr, "example: ./injector --infile=boot.efi --baseseek=409600 --basefile=atv_recv.img \n");
      fprintf(stderr, "\n");
      fprintf(stderr, "\n");
      fprintf(stderr, "Command line arguments:\n");
      fprintf(stderr, "\n");
      fprintf(stderr, "--infile=n where n is file to be injected \n");
      fprintf(stderr, "--basefile=n where n is disk image to inject \n");
      fprintf(stderr, "--baseseek=n where n is the number of bytes to seek in disk image\n");
      fprintf(stderr, "--show-progress        displays the copy progress\n");
      return(0);
      //
    } else {
      fprintf(stderr, "unknown argument %s\n", argv[i]);
      return(-1);
    }
  }

  if (strlen(io_filename) == 0) {
    fprintf(stderr, "injector --help\n");
	return(-1);
  }
  if (strlen(io_basename) == 0) {
    fprintf(stderr, "injector --help\n");
	return(-1);
  }

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


  return((int)0);
}
//________________________________________________________________________________
//________________________________________________________________________________
//________________________________________________________________________________
void signal_control_c(int value)
{
  // when the signal handler is called, the signal handler for 
  //  that particular signal is reset to the default handler
  // so to keep getting these signals we need to reset signal handler within itself
  //signal(SIGINT, signal_control_c);
  printf("\nAbort    :\n");
  fflush(stdout);
}
//________________________________________________________________________________
void  millisecond_sleep(int milliseconds)
{
  timeval    t;
  
  t.tv_sec = milliseconds / 1000;
  t.tv_usec = (milliseconds % 1000 ) *1000;
  select(0, NULL, NULL, NULL, &t);
}
//________________________________________________________________________________
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
//________________________________________________________________________________
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
