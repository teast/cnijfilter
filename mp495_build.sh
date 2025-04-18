#!/bin/bash

# This script will try and build driver for mp495 on an 64bit system.

DESTDIR=/opt/mp495
ROOT=`pwd`
LOGS=$ROOT/logs
ARCH=libs_bin64

abort () {

    echo $1
    exit $2;
}

compile () {
    echo "  $1..."
    LFILE=`echo "$1" | tr / _`
    pushd $1 > /dev/null 2>&1 || abort "could not change to $1 folder" 1
    make > $LOGS/$LFILE.make.log 2>&1 || abort "Error compiling $1" 1
    popd > /dev/null
}

installLibrary () {
    echo "  $1..."
    LFILE=`echo "$1" | tr / _`
    pushd $1 > /dev/null 2>&1 || abort "could not change to $1 folder" 1
    make install > $LOGS/$LFILE.install.log 2>&1 || abort "Error installing $1" 1
    popd > /dev/null
}

cleanLibrary () {
    echo "  $1..."
    LFILE=`echo "$1" | tr / _`
    pushd $1 > /dev/null 2>&1 || abort "could not change to $1 folder" 1
    make clean > $LOGS/$LFILE.clean.log 2>&1 || abort "Error cleaning $1" 1
    make distclean > $LOGS/$LFILE.clean.log 2>&1 || abort "Error cleaning $1" 1
    popd > /dev/null
}

doSymlink () {
    if [ "$3" = "dry" ]; then
        echo "  ln -s $1 $2"
        return
    fi

    ln -s $1 $2 >> $LOGS/symlinks.log 2>&1 && return

    FILENAME=`basename $1`
    TARGET=`readlink $2/$FILENAME`

    echo "could not do a symlink from $1 to $2. It may already exist and if so it points to '$TARGET'"
    exit 1
}

configureAll () {
    echo "Configuring common libraries..."
    echo "  libs..."
    pushd libs > /dev/null 2>&1 || abort "could not change to libs folder" 1
    ./autogen.sh --prefix=$DESTDIR > $LOGS/libs.autogen.log 2>&1
    popd > /dev/null


    echo "  cngpij.."
    pushd cngpij > /dev/null 2>&1 || abort "could not change to cngpij folder" 1
    ./autogen.sh --prefix=$DESTDIR --enable-progpath=$DESTDIR/bin > $LOGS/cngpij.autogen.log 2>&1
    popd > /dev/null

    echo "  pstocanonij.."
    pushd pstocanonij > /dev/null 2>&1 || abort "could not change to pstocanonij folder" 1
    ./autogen.sh --prefix=$DESTDIR --enable-progpath=$DESTDIR/bin > $LOGS/pstocanonij.autogen.log 2>&1
    popd > /dev/null


    echo "  backend.."
    pushd backend > /dev/null 2>&1 || abort "could not change to backend folder" 1
    cat src/Makefile.am | sed "s|backend_bindir.*|backend_bindir = $DESTDIR/lib/cups/backend|g" > src/Makefile.am~ || abort "Could not change backend_bindir configuration in backend/src/Makefile.am" 1
    mv src/Makefile.am~ src/Makefile.am || abort "Could not update original backend/src/Makefile.am with backend_bindir changes" 1
    ./autogen.sh --prefix=$DESTDIR --enable-progpath=$DESTDIR/bin > $LOGS/backend.autogen.log 2>&1
#    ./configure --prefix=$DESTDIR --enable-progpath=$DESTDIR/bin > $LOGS/backend.configure.log 2>&1
    popd > /dev/null

    echo "  backendnet.."
    pushd backendnet > /dev/null 2>&1 || abort "could not change to backendnet folder" 1
    cat backend/Makefile.am | sed "s|backendnet_bindir.*|backendnet_bindir = $DESTDIR/lib/cups/backend|g" > backend/Makefile.am~  || abort "Could not change backendnet_bindir configuration in backendnet/backend/Makefile.am" 1
    mv backend/Makefile.am~ backend/Makefile.am || abort "Could not update original backendnet/backend/Makefile.am with backendnet_bindir changes" 1
    ./autogen.sh --prefix=$DESTDIR --enable-progpath=$DESTDIR/bin LDFLAGS="-L$ROOT/com/$ARCH" > $LOGS/backendnet.autogen.log 2>&1
    popd > /dev/null

    echo "  cngpijmon/cnijnpr.."
    pushd cngpijmon/cnijnpr > /dev/null 2>&1 || abort "could not change to cngpijmon/cnijnpr folder" 1
    ./autogen.sh --prefix=$DESTDIR > $LOGS/cnijnpr.autogen.log 2>&1
    popd > /dev/null


    echo "Configuring printer specific libraries..."

    echo "  ppd.."
    pushd ppd > /dev/null 2>&1 || abort "could not change to ppd folder" 1
    ./autogen.sh --prefix=$DESTDIR --enable-ppdpath=$DESTDIR/share/ppd --program-suffix=mp495  > $LOGS/ppd.autogen.log 2>&1
    popd > /dev/null

    echo "  cnijfilter.."
    pushd cnijfilter > /dev/null 2>&1 || abort "could not change to cnijfilter folder" 1
    ./autogen.sh --prefix=$DESTDIR --enable-libpath=$DESTDIR/lib/bjlib --enable-binpath=$DESTDIR/bin --program-suffix=mp495 > $LOGS/cnijfilter.autogen.log 2>&1
    popd > /dev/null

    echo "  printui.."
    pushd printui > /dev/null 2>&1 || abort "could not change to printui folder" 1
    ./autogen.sh --prefix=$DESTDIR --program-suffix=mp495 --datadir=$DESTDIR/share > $LOGS/printui.autogen.log 2>&1
    popd > /dev/null

    echo "  lgmon.."
    pushd lgmon > /dev/null 2>&1 || abort "could not change to lgmon folder" 1
    ./autogen.sh --prefix=$DESTDIR --enable-progpath=$DESTDIR/bin --program-suffix=mp495 > $LOGS/lgmon.autogen.log 2>&1
    popd > /dev/null

    echo "  cngpijmon.."
    pushd cngpijmon > /dev/null 2>&1 || abort "could not change to cngpijmon folder" 1
    ./autogen.sh --prefix=$DESTDIR --enable-progpath=$DESTDIR/bin --program-suffix=mp495 --datadir=$DESTDIR/share > $LOGS/cngpijmon.autogen.log 2>&1
    popd > /dev/null
}

compileAll () {
    echo "Compiling all common libraries..."

    compile libs
    compile cngpij
    compile pstocanonij
    compile backend
    compile backendnet

    #This needs to be built before cngpijmno/cnijnpr or else you will have en problem with "-lbscc2sts" flag during compilation of cnijnpr
    compile lgmon

    compile cngpijmon/cnijnpr

    echo "Compiling printer specific libraries..."

    compile ppd
    compile cnijfilter
    compile printui
    compile cngpijmon
}

installAll () {
    echo "Creating destinatino folders..."
    mkdir -p $DESTDIR/lib || abort "Could not create $DESTDIR/lib folder" 1
    mkdir -p $DESTDIR/lib/bjlib || abort "Could not create $DESTDIR/lib/bjlib folder" 1

    echo "Installing all common libraries..."
    installLibrary libs
    installLibrary cngpij
    installLibrary pstocanonij
    installLibrary backend
    installLibrary backendnet
    installLibrary cngpijmon/cnijnpr

    # Not sure if we realy need an cnijnpr with suffix.. but here we got it anyway...
    cp $DESTDIR/bin/cnijnpr $DESTDIR/bin/cnijnprmp495 || abort "Could not duplicate cnijnpr with suffix" 1

    echo "Installing printer specific libraries..."

    installLibrary ppd
    installLibrary cnijfilter
    installLibrary printui
    installLibrary lgmon
    installLibrary cngpijmon

    echo "Installing not-compiled files..."
    install -c -m 755 com/$ARCH/libcnnet.so.* $DESTDIR/lib || abort "Could not install libcnnet.so.*" 1
    # TODO: No lp owner for cnnet.ini in gentoo at the moment... 
    #install -c -m 644 -o lp -g lp com/ini/cnnet.ini $DESTDIR/lib/bjlib || abort "Could not install cnnet.ini" 1
    install -c -m 644 com/ini/cnnet.ini $DESTDIR/lib/bjlib || abort "Could not install cnnet.ini" 1
    install -c -m 755 com/$ARCH/libcnnet* $DESTDIR/lib || abort "Could not install libcnnet*" 1

    echo "  mp495 specific files.."
    install -c -m 755 369/$ARCH/libcnbpcmcm369.so.* $DESTDIR/lib || abort "Could not install libcnbpcmcm369.so.*" 1
    install -c -m 755 369/$ARCH/libcnbpcnclapi369.so.* $DESTDIR/lib || abort "Could not install libcnbpcnclapi369.so.*" 1
    install -c -m 755 369/$ARCH/libcnbpcnclbjcmd369.so.* $DESTDIR/lib || abort "Could not install libcnbpcnclbjcmd369.so.*" 1
    install -c -m 755 369/$ARCH/libcnbpcnclui369.so.* $DESTDIR/lib || abort "Could not install libcnbpcnclui369.so.*" 1
    install -c -m 755 369/$ARCH/libcnbpess369.so.* $DESTDIR/lib || abort "Could not install libcnbpess369.so.*" 1
    install -c -m 755 369/$ARCH/libcnbpo369.so.* $DESTDIR/lib || abort "Could not install libcnbpo369.so.*" 1
    install -c -m 644 369/database/cifmp495.conf $DESTDIR/lib/bjlib || abort "Could not install cifmp495.conf" 1
    install -c -m 644 369/database/cnb_3690.tbl $DESTDIR/lib/bjlib || abort "Could not install cnb_3690.tbl" 1
    install -c -m 644 369/database/cnbpname369.tbl $DESTDIR/lib/bjlib || abort "Could not install cnbpname369.tbl" 1
}

cleanAll () {
    echo "cleaning all common libraries..."

    cleanLibrary libs || 
    cleanLibrary cngpij
    cleanLibrary pstocanonij
    cleanLibrary backend
    cleanLibrary backendnet
    cleanLibrary cngpijmon/cnijnpr

    echo "Cleaning printer specific libraries..."

    cleanLibrary ppd
    cleanLibrary cnijfilter
    cleanLibrary printui
    cleanLibrary lgmon
    cleanLibrary cngpijmon
}

symlinkAll () {
    echo "Symlinks for bin files..."
    doSymlink "$DESTDIR/bin/cngpij" "/usr/bin" $1
    doSymlink "$DESTDIR/bin/cnijnetprn" "/usr/bin" $1
    doSymlink "$DESTDIR/bin/cnijnpr" "/usr/bin" $1

    echo "Symlinks for lib files..."
    doSymlink "$DESTDIR/lib/bjlib" "/usr/lib" $1
    doSymlink "$DESTDIR/lib/libcnbpcmcm369.so.8.0.1" "/usr/lib" $1
    doSymlink "$DESTDIR/lib/libcnbpcnclapi369.so.3.5.0" "/usr/lib" $1
    doSymlink "$DESTDIR/lib/libcnbpess369.so.3.3.3" "/usr/lib" $1
    doSymlink "$DESTDIR/lib/libcnbpcnclbjcmd369.so.3.3.0" "/usr/lib" $1
    doSymlink "$DESTDIR/lib/libcnbpo369.so.1.0.2" "/usr/lib" $1
    doSymlink "$DESTDIR/lib/libcnbpcnclui369.so.3.6.0" "/usr/lib" $1

    doSymlink "/usr/lib/libcnbpcmcm369.so.8.0.1" "/usr/lib/libcnbpcmcm369.so" $1
    doSymlink "/usr/lib/libcnbpcnclapi369.so.3.5.0" "/usr/lib/libcnbpcnclapi369.so" $1
    doSymlink "/usr/lib/libcnbpess369.so.3.3.3" "/usr/lib/libcnbpess369.so" $1
    doSymlink "/usr/lib/libcnbpcnclbjcmd369.so.3.3.0" "/usr/lib/libcnbpcnclbjcmd369.so" $1
    doSymlink "/usr/lib/libcnbpo369.so.1.0.2" "/usr/lib/libcnbpo369.so" $1
    doSymlink "/usr/lib/libcnbpcnclui369.so.3.6.0" "/usr/lib/libcnbpcnclui369.so" $1

    doSymlink "/opt/mp495/lib/libcnnet.so.1.2.0" "/usr/lib" $1
    doSymlink "/opt/mp495/lib/libcnnet.so" "/usr/lib" $1

    echo "Symlinks for cups specific files..."
    doSymlink "/opt/mp495/lib/cups/backend/cnijnet" "/usr/libexec/cups/backend" $1
    doSymlink "/opt/mp495/lib/cups/backend/cnijusb" "/usr/libexec/cups/backend" $1
    doSymlink "/opt/mp495/lib/cups/filter/pstocanonij" "/usr/libexec/cups/filter" $1

    echo "Symlinks for share files..."
    doSymlink "/opt/mp495/share/cngpijmonmp495" "/usr/share" $1
    doSymlink "/opt/mp495/share/printuimp495" "/usr/share" $1
    doSymlink "/opt/mp495/share/ppd/canonmp495.ppd" "/usr/share/cups/model" $1
}

#
# Main entry
#

mkdir -p $DESTDIR || abort "Could not create $DESTDIR", 1 
mkdir -p $LOGS || abort "Could not create $LOGS", 1


if [ "$1" = "configure" ]; then
    configureAll
elif [ "$1" = "build" ]; then
    compileAll
elif [ "$1" = "install" ]; then
    installAll
elif [ "$1" = "clean" ]; then
    cleanAll
    #make clean > $LOGS/general.clean.log 2>&1 || abort "Error doing general cleanup" 1
elif [ "$1" = "symlink" ]; then
    symlinkAll
elif [ "$1" = "symlinkdry" ]; then
    symlinkAll "dry"
elif [ "$1" = "all" ]; then
    configureAll
    compileAll
    installAll
    echo "TODO: symlink"
else
    echo "This script requires instructions to work"
    echo ""
    echo -e "\tconfigure\tneeds to be run at least once before a build"
    echo -e "\tbuild\t\tbuilds all libraries. needs to be run before install"
    echo -e "\tinstall\t\tinstalls all libraries to destination folder"
    echo -e "\tsymlink\t\tcreates symlink in /usr/bin, /usr/lib, /usr/libexec/cups etc. NOTE! Requires root privilege"
    echo -e "\tsymlinkdry\toutput all symlink commands that woul be run if it was an 'symlink' command"
    echo -e "\tclean\t\tclean up of auto-generated build files"
    echo -e "\tall\t\truns configure, build, install and symlink. NOTE! Requires root privilege due to symlink"
    echo ""
    echo -e "DESTDIR: $DESTDIR"
    echo -e "LOGS: $LOGS"
    echo ""
    echo ""
fi
