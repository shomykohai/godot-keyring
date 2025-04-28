{ pkgs ? import <nixpkgs> {} }:

pkgs.mkShell {
  name = "godot-keyring-build-env";

  nativeBuildInputs = [
    pkgs.scons
    pkgs.pkg-config
  ];

  buildInputs = [
    pkgs.libsecret
    # Windows builds
    pkgs.pkgsCross.mingwW64.buildPackages.gcc 
  ];

  shellHook = ''
    echo "🛠 Welcome to Godot Keyring dev shell!"
    echo "Available commands:"
    echo "» Use: compile        # Linux build"
    echo "» Use: compile -w     # Windows (MinGW) build"
    echo "» Use: compile -r     # Release build"
    echo "» Use: compile -d     # Debug build"
    echo "» Pass extra scons flags as needed!"

    compile() {
      local mode=""
      local platform="linux"
      local mingwFlag=""

      # Handle the -r and -d flags for release and debug builds
      while [[ "$1" == "-r" || "$1" == "-d" ]]; do
        if [[ "$1" == "-r" ]]; then
          mode="template_release"
          shift
        elif [[ "$1" == "-d" ]]; then
          mode="template_debug"
          shift
        fi
      done

      # Check if we're cross-compiling for Windows
      if [[ "$1" == "-w" ]]; then
        platform="windows"
        mingwFlag="use_mingw=yes"
        shift  # Remove the -w flag
        echo "🔧 Cross-compiling for Windows with MinGW..."
      else
        echo "🔧 Building for Linux..."
      fi

      # Default to debug if no mode was set
      if [[ -z "$mode" ]]; then
        echo "🛠 No build mode specified, compiling both release and debug builds..."
        # Compile both release and debug builds
        scons platform=$platform target=template_debug $mingwFlag "$@"
        scons platform=$platform target=template_release $mingwFlag "$@"
      else
        # Pass the mode and MingwFlag if it's Windows
        scons platform=$platform target=$mode $mingwFlag "$@"
      fi
    }

    export -f compile
    '';
}
