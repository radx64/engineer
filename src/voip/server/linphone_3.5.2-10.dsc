-----BEGIN PGP SIGNED MESSAGE-----
Hash: SHA1

Format: 3.0 (quilt)
Source: linphone
Binary: linphone, linphone-nogtk, linphone-common, liblinphone4, liblinphone-dev, libmediastreamer1, libmediastreamer-dev, libortp8, libortp-dev, linphone-dbg
Architecture: any all
Version: 3.5.2-10
Maintainer: Debian VoIP Team <pkg-voip-maintainers@lists.alioth.debian.org>
Uploaders: Mark Purcell <msp@debian.org>, Kilian Krause <kilian@debian.org>, Tzafrir Cohen <tzafrir@debian.org>
Homepage: http://www.linphone.org/
Standards-Version: 3.9.3
Vcs-Browser: http://anonscm.debian.org/viewvc/pkg-voip/linphone/trunk/
Vcs-Svn: svn://svn.debian.org/pkg-voip/linphone/trunk/
Build-Depends: debhelper (>= 9), autoconf, automake1.9, autotools-dev, libtool, pkg-config, intltool, doxygen, libncurses5-dev, libreadline6-dev, libglib2.0-dev, libosip2-dev (>= 3.5.0), libexosip2-dev (>= 3.5.0), libsrtp-dev [!hurd-any !sparc], libasound2-dev [linux-any], libv4l-dev [linux-any], libspeex-dev, libspeexdsp-dev, libsamplerate0-dev, libxml-parser-perl, libgsm1-dev, libgtk2.0-dev, libglade2-dev, libtheora-dev, libxv-dev, libavcodec-dev, libreadline-dev, libsdl1.2-dev, libswscale-dev
Package-List: 
 liblinphone-dev deb libdevel optional
 liblinphone4 deb libs optional
 libmediastreamer-dev deb libdevel optional
 libmediastreamer1 deb libs optional
 libortp-dev deb libdevel optional
 libortp8 deb libs optional
 linphone deb sound optional
 linphone-common deb sound optional
 linphone-dbg deb debug extra
 linphone-nogtk deb sound optional
Checksums-Sha1: 
 d0dde9d421b7cf6893c8e5acb969d5bd4a04a231 8338517 linphone_3.5.2.orig.tar.gz
 d654d3f9e3718f06ff18e342d1dce2e62e48ff7d 15653 linphone_3.5.2-10.debian.tar.gz
Checksums-Sha256: 
 da37d5e539e3f8aaa44039aa52ed032ef372e7481d1b3ce68317bf79aa8a6020 8338517 linphone_3.5.2.orig.tar.gz
 8f3ef48c2deedbe6ba7a5556974c2b3931cee9ad631543a3fd75832bc05ab050 15653 linphone_3.5.2-10.debian.tar.gz
Files: 
 4be6e940372dba1f6793aef849c1ff0d 8338517 linphone_3.5.2.orig.tar.gz
 e535ec8080003398f296466054cdd7a9 15653 linphone_3.5.2-10.debian.tar.gz

-----BEGIN PGP SIGNATURE-----
Version: GnuPG v1.4.12 (GNU/Linux)

iEYEARECAAYFAk/nDW8ACgkQoCzanz0IthILNQCfeFxKzoWcXH0I5uJOBiHpK+dc
19kAn3w4z7MLnW+zznqAPMS9x97wZA/M
=verG
-----END PGP SIGNATURE-----
