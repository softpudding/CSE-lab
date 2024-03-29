#ifndef yfs_client_h
#define yfs_client_h

#include <string>
//#include "yfs_protocol.h"
#include "extent_client.h"
#include <vector>
#define DIRENTSIZE 128
#define MAX(a,b) ((a)>(b)?(a):(b))

//#include "lock_client.h"
#include "lock_client_cache.h"
class yfs_client {
  extent_client *ec;
  lock_client_cache * lc;
  //lock_client *lc;
 public:

  typedef unsigned long long inum;
  enum xxstatus { OK, RPCERR, NOENT, IOERR, EXIST };
  typedef int status;

  struct fileinfo {
    unsigned long long size;
    unsigned long atime;
    unsigned long mtime;
    unsigned long ctime;
  };
  struct dirinfo {
    unsigned long atime;
    unsigned long mtime;
    unsigned long ctime;
  };
  struct dirent {
    char name[DIRENTSIZE-sizeof(yfs_client::inum)];//128 - 8 = 120
    yfs_client::inum inum;
  };

 private:
  static std::string filename(inum);
  static inum n2i(std::string);

 public:
  yfs_client();
  yfs_client(std::string, std::string);

  bool isfile(inum);
  bool isdir(inum);

  int getfile(inum, fileinfo &);
  int getdir(inum, dirinfo &);

  int setattr(inum, size_t);
  int lookup(inum, const char *, bool &, inum &);
  int create(inum, const char *, mode_t, inum &);
  int readdir(inum, std::list<dirent> &);
  int write(inum, size_t, off_t, const char *, size_t &);
  int read(inum, size_t, off_t, std::string &);
  int unlink(inum,const char *);
  int mkdir(inum , const char *, mode_t , inum &);
  
  /** you may need to add symbolic link related methods here.*/
  int softpudding_symlink(const char * link, inum parent, const char * name, inum & ino); 
  void softpudding_readlink(inum strange_ino, std::string & content);
  int readdir_ (inum,std::list<dirent> & );
  int lookup_ (inum,const char *,bool &, inum &);
  bool isdir_ (inum);
  int setattr_(inum, size_t);
};

#endif 

