<h1 align="center">
<img src="./keyring.svg" alt="Godot Keyring" width=128><br>
🔑 Godot Keyring
</h1>

"Godot Keyring" is a Godot addon to interact with the OS keyring.<br>

The addon itself is a wrapper of [keychain](https://github.com/hrantzsch/keychain) by [@hrantzsch](https://github.com/hrantzsch/) to allow cross-platform support.

## 📙 Usage

```gdscript
#some_node.gd

func store_password(user: String, password: String) -> void:
    if password.is_empty() or user.is_empty():
        print("Trying to store non valid credentials.")
        return

    Keyring.set_password("my_cool_application", "credentials", user, password)

func login(user: String) -> void:
    var password := Keyring.get_password("my_cool_application", "credentials", user)
    if password.is_empty():
        return
    
    # Use password
    ...

```

## 🛠️ Building

**Requirements**
* [SCons](https://www.scons.org/)
* [python3](https://www.python.org/)
* libsecret (Linux only)

Run the scons command to build the addon:
```bash
$ scons
```

You can also specify to which platform compile:
```bash
$ scons platform=windows
```

## ✨ Credits
"Godot Keyring" logo by [@archaeopteryz](https://github.com/archaeopteryz)

## 💼 License
Licensed under the MIT license, see [LICENSE](LICENSE.md)

The code in ["src/keychain"](src/keychain/) is licensed under the MIT license, see [keychain/LICENSE](src/keychain/LICENSE)
