#ifndef GODOT_KEYRING_H
#define GODOT_KEYRING_H

#include <godot_cpp/classes/ref_counted.hpp>
#include "keychain/keychain.h"

namespace godot {

class Keyring : public RefCounted {
    GDCLASS(Keyring, RefCounted);

    static Keyring* singleton;

    protected:
        static void _bind_methods();

    public:
        enum KeyringError {
            NO_ERROR = 0,
            GENERIC_ERROR = 1,
            NOT_FOUND = 2,
            PASSWORD_TOO_LONG = 3, // Windows only
            ACCESS_DENIED = 4 // macOS only
        };

        ~Keyring();
        Keyring();

        static Keyring* get_singleton();

        // Methods
        String get_password(const String &package, const String &service, const String &user);
        Keyring::KeyringError set_password(const String &package, const String &service, const String &user, const String &password);
        Keyring::KeyringError delete_password(const String &package, const String &service, const String &user);
};

} //namespace godot

VARIANT_ENUM_CAST(Keyring::KeyringError);

#endif // GODOT_KEYRING_H