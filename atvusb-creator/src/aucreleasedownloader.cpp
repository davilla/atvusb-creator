#include "aucreleasedownloader.h"

#include <iostream>
#include <QtCore/QDir>
#include <QtCore/QUrl>
#include <QtCore/QFile>
#include <QtCore/QFileInfo>
#include <QtNetwork/QHttp>

AucReleaseDownloader::AucReleaseDownloader(){
    connect(&m_http, SIGNAL(done(bool)), this, SLOT(done(bool)));
    connect(&m_http, SIGNAL(dataReadProgress(int, int)), this, SLOT(httpProgress(int, int)));
}

AucReleaseDownloader::~AucReleaseDownloader(){
}

void AucReleaseDownloader::download(QString f_destination_folder, QString f_url){
  emit status(QString("Downloading %1...").arg(f_url));
  QUrl download_url = QUrl(f_url);
  if( !download_url.isValid() ) {
    emit downloadComplete("Not a valid URL!");
    return;
  }
  if( download_url.scheme() != "http") {
    emit downloadComplete("Sorry, only http is currently supported!");
    return;
  }
  //assemble and clean destination path
  QString dst_path = f_destination_folder + QDir::separator() + QFileInfo(f_url).fileName();
  if ( QFile::exists(dst_path) ){
    QFile::remove(dst_path);
  }  
  //setup destination file
  m_destination_file.setFileName( dst_path );
  if(! m_destination_file.open(QIODevice::WriteOnly) ){
    emit downloadComplete(QString("Sorry, cannot open output file %1").arg(m_destination_file.fileName()));
    return;               
  }
  
  m_http.setHost(download_url.host(), download_url.port(80));
  //start download
  m_http.get(download_url.path(), &m_destination_file);    
  //queue close request
  m_http.close();
}

void AucReleaseDownloader::done(bool f_error){
  if(f_error)
    emit downloadComplete(m_http.errorString());
  else{
    m_destination_file.close();
    emit downloadComplete(m_destination_file.fileName());
  }
}

void AucReleaseDownloader::httpProgress(int f_part, int f_total){
  emit maxprogress(f_total);
  emit progress(f_part);
}
