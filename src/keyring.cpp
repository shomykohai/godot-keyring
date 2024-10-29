#include "keyring.hpp"
#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/core/class_db.hpp>

using namespace godot;

Keyring* Keyring::singleton = nullptr;

void Keyring::_bind_methods() {
    // Methods
    ClassDB::bind_method(D_METHOD("get_password", "package", "service", "user"), &Keyring::get_password);
    ClassDB::bind_method(D_METHOD("set_password", "package", "service", "user", "password"), &Keyring::set_password);
    ClassDB::bind_method(D_METHOD("delete_password", "package", "service", "user"), &Keyring::delete_password);

    // Enum Constants
    BIND_ENUM_CONSTANT(NO_ERROR);
    BIND_ENUM_CONSTANT(GENERIC_ERROR);
    BIND_ENUM_CONSTANT(NOT_FOUND);
    BIND_ENUM_CONSTANT(PASSWORD_TOO_LONG);
    BIND_ENUM_CONSTANT(ACCESS_DENIED);
}


Keyring* Keyring::get_singleton() {
    return singleton;
}

Keyring::Keyring() {
    UtilityFunctions::print_verbose("Godot Keyring initialized");
    singleton=this;
}

Keyring::~Keyring() {
    ERR_FAIL_COND(singleton!=this);
    singleton = nullptr;
    UtilityFunctions::print_verbose("Godot Keyring destroyed");
}

String Keyring::get_password(const String &package, const String &service, const String &user) {
    keychain::Error err;

    std::string password = keychain::getPassword(package.utf8().get_data(), service.utf8().get_data(), user.utf8().get_data(), err);

    if (err.type != keychain::ErrorType::NoError) {
        return String();
    }
    return String::utf8(password.c_str());
}

Keyring::KeyringError Keyring::set_password(const String &package, const String &service, const String &user, const String &password) {
    keychain::Error err;

    keychain::setPassword(package.utf8().get_data(), service.utf8().get_data(), user.utf8().get_data(), password.utf8().get_data(), err);
    
    if(err.type == keychain::ErrorType::NoError) {
        return KeyringError::NO_ERROR;
    }

    UtilityFunctions::push_error(String::utf8(err.message.c_str()));

    switch(err.type) {
        case keychain::ErrorType::GenericError:
            return KeyringError::GENERIC_ERROR;
        case keychain::ErrorType::PasswordTooLong:
            return KeyringError::PASSWORD_TOO_LONG;
        case keychain::ErrorType::AccessDenied:
            return KeyringError::ACCESS_DENIED;
        default:
            return KeyringError::GENERIC_ERROR;
    }
}

Keyring::KeyringError Keyring::delete_password(const String &package, const String &service, const String &user) {
    keychain::Error err;

    keychain::deletePassword(package.utf8().get_data(), service.utf8().get_data(), user.utf8().get_data(), err);

    if(err.type == keychain::ErrorType::NoError) {
        return KeyringError::NO_ERROR;
    }

    UtilityFunctions::push_error(String::utf8(err.message.c_str()));

    switch(err.type) {
        case keychain::ErrorType::GenericError:
            return KeyringError::GENERIC_ERROR;
        case keychain::ErrorType::PasswordTooLong:
            return KeyringError::PASSWORD_TOO_LONG;
        case keychain::ErrorType::AccessDenied:
            return KeyringError::ACCESS_DENIED;
        default:
            return KeyringError::GENERIC_ERROR;
    }
}
