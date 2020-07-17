#NDK=/home/dimeo/local/android-sdk/ndk/21.0.6113669
NDK=/home/dimeo/local/Android/Sdk/ndk/21.3.6528147

export TOOLCHAIN=$NDK/toolchains/llvm/prebuilt/linux-x86_64

# Only choose one of these, depending on your device...
#export TARGET=aarch64-linux-android
export TARGET=armv7a-linux-androideabi
#export TARGET=i686-linux-android
#export TARGET=x86_64-linux-android

# Set this to your minSdkVersion.
export API=21
# Configure and build.
#export AR=$TOOLCHAIN/bin/$TARGET-ar
export AR=$TOOLCHAIN/bin/arm-linux-androideabi-ar
export AS=$TOOLCHAIN/bin/arm-linux-androideabi-as
export CC=$TOOLCHAIN/bin/$TARGET$API-clang
export CXX=$TOOLCHAIN/bin/$TARGET$API-clang++
export LD=$TOOLCHAIN/bin/arm-linux-androideabi-ld
export RANLIB=$TOOLCHAIN/bin/arm-linux-androideabi-ranlib
export STRIP=$TOOLCHAIN/bin/arm-linux-androideabi-strip

export LDFLAGS="$LDFLAGS -L/scratch/guile_compilation/local/lib"
export CPPFLAGS="$CPPFLAGS -I/scratch/guile_compilation/local/include"

export GUILE_FOR_BUILD=/scratch/guile_compilation/guile_for_build/bin/guile

# This one is probably a disaster:
export LDFLAGS="-L/home/dimeo/local/Android/Sdk/ndk/21.3.6528147/toolchains/llvm/prebuilt/linux-x86_64/sysroot/usr/lib/arm-linux-androideabi/21 -lm"

echo "Execute: ./configure --host $TARGET"

