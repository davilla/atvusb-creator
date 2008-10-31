
#include <QtCore/QDir>
#include <QtCore/QProcess>
#include <QtCore/QFileInfo>
#include <QtCore/QCryptographicHash>
#include "atvusbcreatorbase.h"
#include <cassert>

//---------------------------------------------------------------------- 
//---------------------------------------------------------------------- 
AtvUsbCreatorBase::AtvUsbCreatorBase() : QObject() {
  // find the launch path
  QDir        current_dir( QString(".") );
  
  // this folder should already exists as the payloads will be extracted from it
  m_payload_folder = current_dir.absolutePath() + QDir::separator() + "payloads";

  m_tmp_folder = current_dir.tempPath();
  // check for staging/downloads folders, make them if they don't exist
  m_staging_folder = current_dir.absolutePath() + QDir::separator() + "staging";
  m_download_folder = current_dir.absolutePath() + QDir::separator() + "downloads";
  if ( !current_dir.exists(m_staging_folder)) {
    current_dir.mkdir(m_staging_folder);
  }
  if ( !current_dir.exists(m_download_folder)) {
    current_dir.mkdir(m_download_folder);
  }

  // boot.efi is always extracted to staging/boot.efi
  m_bootefi_path = m_staging_folder + QDir::separator() + "boot.efi";

  // load up info_data from the default lists
  m_info_data.populateWithDefaults();
}

//---------------------------------------------------------------------- 
AtvUsbCreatorBase::~AtvUsbCreatorBase() {

}

//---------------------------------------------------------------------- 
void AtvUsbCreatorBase::setDMGPath(const QString &fcr_path) {
  m_dmg_path = fcr_path;
}

//---------------------------------------------------------------------- 
const QString& AtvUsbCreatorBase::getcrDMGPath() const {
  return m_dmg_path;
}

//---------------------------------------------------------------------- 
const QString& AtvUsbCreatorBase::getcrBootEFIPath() const {
  return m_bootefi_path;
}

//---------------------------------------------------------------------- 
const QString& AtvUsbCreatorBase::getcrDownloadFolder(){
  return m_download_folder;
}

//---------------------------------------------------------------------- 
void AtvUsbCreatorBase::setDrive(const QString &fcr_path) {
  m_drive = fcr_path;
}

//---------------------------------------------------------------------- 
const QStringList& AtvUsbCreatorBase::getcrDevices(){
  return m_devices;
}

//---------------------------------------------------------------------- 
InfoData& AtvUsbCreatorBase::getrInfoData(){
  return m_info_data;
}

//---------------------------------------------------------------------- 
Logger& AtvUsbCreatorBase::logger() {
  return m_logger;
}

//---------------------------------------------------------------------- 
QString AtvUsbCreatorBase::do_process(const QString &program, const QStringList &arguments) {
  QString         result;
  QProcess        process;

  process.start(program, arguments);
  if (!process.waitForStarted())
    throw AtvUsbCreatorException((program + " could not be started").toStdString());
  if (!process.waitForFinished())
    throw AtvUsbCreatorException((program + " exited with failure %1").arg(process.exitCode()).toStdString());

  result = QString::fromLatin1(process.readAllStandardOutput());
  
  return(result);
}

//----------------------------------------------------------------------   
void AtvUsbCreatorBase::mount_disk() {
  assert(0 && "implement me!");
}

//----------------------------------------------------------------------   
void AtvUsbCreatorBase::umount_disk() {
  assert(0 && "implement me!");
}
//----------------------------------------------------------------------   
void AtvUsbCreatorBase::detect_removable_drives(){
  assert(0 && "implement me!");
}

//----------------------------------------------------------------------   
bool AtvUsbCreatorBase::create_image(){
  assert(0 && "implement me!");
  return false;
}

//----------------------------------------------------------------------   
bool AtvUsbCreatorBase::partition_disk(){
  assert(0 && "implement me!");
  return false;
}

//----------------------------------------------------------------------   
bool AtvUsbCreatorBase::install_recovery(){
  assert(0 && "implement me!");
  return false;
}

//----------------------------------------------------------------------   
bool AtvUsbCreatorBase::install_patchstick(){
  assert(0 && "implement me!");
  return false;
}

//----------------------------------------------------------------------   
bool AtvUsbCreatorBase::install_payload(INSTALLER const& fcr_installer, QString const& fcr_mount_point){
  assert(0 && "implement me!");
  return false;
}

//----------------------------------------------------------------------   
void AtvUsbCreatorBase::extract_recovery(){
  const QString hfs_image_path = m_staging_folder + QDir::separator() + QString::fromStdString(getrInfoData().hfs_info().name);
  if(!QFile::exists(hfs_image_path)){
    emit status("Extracting recovery seed ...");
    const QString archive_path = m_payload_folder + QDir::separator() + QString::fromStdString(getrInfoData().hfs_info().file);
    extract_7z_image(archive_path, hfs_image_path, m_staging_folder);
  }
}

//----------------------------------------------------------------------   
bool AtvUsbCreatorBase::verify_image(){
  const int READBLOCK_SIZE=1024*1024;
  QFile file(m_dmg_path);
  emit maxprogress(file.size());
  int read_bytes = 0;
	QCryptographicHash sha1Hash(QCryptographicHash::Sha1);
	if (file.open(QIODevice::ReadOnly | QIODevice::Unbuffered)) {		
		while (!file.atEnd()){
			sha1Hash.addData(file.read(READBLOCK_SIZE));
      read_bytes += READBLOCK_SIZE;
      emit progress(read_bytes);
    }
	}
	file.close();
  const QByteArray given(QByteArray::fromHex(getrInfoData().atv_dmg_info().sha1.c_str()));
  if(given == sha1Hash.result())
    return true;
  return false;
}

