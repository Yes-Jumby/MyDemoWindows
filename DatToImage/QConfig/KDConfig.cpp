#include "KDConfig.h"

void CKDConfig::setParameterFile( const QString& filename ) {
    if ( config_ == nullptr ) {
        config_ = std::shared_ptr<CKDConfig>(new CKDConfig);
    }
    config_->file_ = std::shared_ptr<QSettings>(new QSettings(filename,QSettings::IniFormat));
    //config_->file_->beginGroup("System");
}

CKDConfig::~CKDConfig(){
    //config_->file_->endGroup();
}
int CKDConfig::getInt( const QString& key){
        return (CKDConfig::config_->file_->value(key).toInt()) ;
}
QString CKDConfig::getQString( const QString& key ){
        return (CKDConfig::config_->file_->value(key).toString()) ;
}
std::shared_ptr<CKDConfig> CKDConfig::config_ = nullptr;
