#ifndef KDCONFIG_H
#define KDCONFIG_H
#include <memory>
#include <QSettings>
class CKDConfig
{
public:
    ~CKDConfig();
    // set a new config file
    static void setParameterFile( const QString& filename );
    template< typename T >
    static T getValue( const QString& key) {
        return CKDConfig::config_->file_->value(key).value<T>();
    }
    template< typename T >
    static void setValue( const QString& key ,T value) {
        CKDConfig::config_->file_->setValue(key,value);
    }
private:
    // access the parameter values
    static int getInt( const QString& key);
    static QString getQString( const QString& key );
    static std::shared_ptr<CKDConfig> config_;
    std::shared_ptr<QSettings> file_;
    CKDConfig () {}
};

#endif // KDCONFIG_H
