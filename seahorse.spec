Name:		seahorse
Version:	3.8.2
Release:	3%{?dist}
Summary:	A GNOME application for managing encryption keys
Group:		User Interface/Desktops
# seahorse is GPLv2+
# libcryptui is LGPLv2+
License:        GPLv2+ and LGPLv2+
URL:            http://projects.gnome.org/seahorse/
#VCS: git:git://git.gnome.org/seahorse
Source:         http://download.gnome.org/sources/seahorse/3.8/%{name}-%{version}.tar.xz

BuildRequires:  glib2-devel
BuildRequires:  gtk3-devel
BuildRequires:  gcr-devel
BuildRequires:  desktop-file-utils
BuildRequires:  gettext
BuildRequires:  gpgme-devel >= 1.0
BuildRequires:  gnupg2
BuildRequires:  itstool
BuildRequires:  libsoup-devel
BuildRequires:  openldap-devel
BuildRequires:  libnotify-devel
BuildRequires:  openssh-clients
BuildRequires:  libsecret-devel
BuildRequires:  avahi-devel
BuildRequires:  avahi-glib-devel
BuildRequires:  intltool
BuildRequires:  dbus-glib-devel
BuildRequires:  gobject-introspection-devel >= 0.6.4
BuildRequires:  libSM-devel
BuildRequires:  GConf2-devel
# for g-ir-scanner
BuildRequires:  libtool
Requires(post): desktop-file-utils
Requires(post): /usr/bin/gtk-update-icon-cache
Requires(postun): desktop-file-utils
Requires(postun): shared-mime-info
Requires(postun): /usr/bin/gtk-update-icon-cache

# https://bugzilla.redhat.com/show_bug.cgi?id=474419
# https://bugzilla.redhat.com/show_bug.cgi?id=587328
Requires:       pinentry-gui

Obsoletes: gnome-keyring-manager
Obsoletes: seahorse-devel < 3.1.4-2
# Self-obsoletes to assist with seahorse-sharing package split
Obsoletes: seahorse < 3.1.4

%description
Seahorse is a graphical interface for managing and using encryption keys.
It also integrates with nautilus, gedit and other places for encryption
operations.  It is a keyring manager.


%prep
%setup -q


%build
GNUPG=/usr/bin/gpg2 ; export GNUPG ; %configure

# drop unneeded direct library deps with --as-needed
# libtool doesn't make this easy, so we do it the hard way
sed -i -e 's/ -shared / -Wl,-O1,--as-needed\0 /g' -e 's/    if test "$export_dynamic" = yes && test -n "$export_dynamic_flag_spec"; then/      func_append compile_command " -Wl,-O1,--as-needed"\n      func_append finalize_command " -Wl,-O1,--as-needed"\n\0/' libtool

make %{?_smp_mflags}
# cleanup permissions for files that go into debuginfo
find . -type f -name "*.c" -exec chmod a-x {} ';'

%install
make install DESTDIR=$RPM_BUILD_ROOT
#mkdir -p $RPM_BUILD_ROOT/etc/X11/xinit/xinitrc.d/
#install -m 755 %{SOURCE1} $RPM_BUILD_ROOT/etc/X11/xinit/xinitrc.d/seahorse-agent.sh

%find_lang seahorse --with-gnome --all-name

desktop-file-install --delete-original  \
  --dir ${RPM_BUILD_ROOT}%{_datadir}/applications       \
  --add-category GNOME                                  \
  --add-category Utility                                \
  --add-category X-Fedora                               \
  ${RPM_BUILD_ROOT}%{_datadir}/applications/seahorse.desktop

# nuke the icon cache
rm -f ${RPM_BUILD_ROOT}/usr/share/icons/hicolor/icon-theme.cache

find ${RPM_BUILD_ROOT} -type f -name "*.la" -exec rm -f {} ';'
find ${RPM_BUILD_ROOT} -type f -name "*.a" -exec rm -f {} ';'

%pre
%gconf_schema_obsolete seahorse

%post
/sbin/ldconfig
update-mime-database %{_datadir}/mime/ > /dev/null
update-desktop-database %{_datadir}/applications > /dev/null 2>&1 || :
touch --no-create %{_datadir}/icons/hicolor >&/dev/null || :


%postun
/sbin/ldconfig
update-mime-database %{_datadir}/mime/ > /dev/null
update-desktop-database %{_datadir}/applications > /dev/null 2>&1 || :
if [ $1 -eq 0 ]; then
  touch --no-create %{_datadir}/icons/hicolor >&/dev/null|| :
  gtk-update-icon-cache %{_datadir}/icons/hicolor >&/dev/null || :
  glib-compile-schemas %{_datadir}/glib-2.0/schemas &> /dev/null || :
fi

%posttrans
gtk-update-icon-cache %{_datadir}/icons/hicolor >&/dev/null || :
glib-compile-schemas %{_datadir}/glib-2.0/schemas &> /dev/null || :


%files -f %{name}.lang
%doc AUTHORS COPYING NEWS README TODO
%{_bindir}/*
%dir %{_datadir}/%{name}
%{_datadir}/%{name}/*
%{_datadir}/applications/*.desktop
%{_datadir}/icons/hicolor/*/apps/seahorse.png
%{_datadir}/icons/hicolor/*/apps/seahorse-preferences.png
%{_mandir}/man1/*.gz
%dir %{_libdir}/seahorse
%{_libdir}/seahorse/*
%{_datadir}/GConf/gsettings/*.convert
%{_datadir}/glib-2.0/schemas/*.gschema.xml

%changelog
* Fri Jan 24 2014 Daniel Mach <dmach@redhat.com> - 3.8.2-3
- Mass rebuild 2014-01-24

* Fri Dec 27 2013 Daniel Mach <dmach@redhat.com> - 3.8.2-2
- Mass rebuild 2013-12-27

* Tue May 14 2013 Richard Hughes <rhughes@redhat.com> - 3.8.2-1
- Update to 3.8.2

* Tue Apr 16 2013 Richard Hughes <rhughes@redhat.com> - 3.8.1-1
- Update to 3.8.1

* Tue Mar 26 2013 Kalev Lember <kalevlember@gmail.com> - 3.8.0-1
- Update to 3.8.0

* Fri Mar  8 2013 Matthias Clasen <mclasen@redhat.com> 0- 3.7.91-1
- Update to 3.7.91

* Wed Feb 06 2013 Kalev Lember <kalevlember@gmail.com> - 3.7.5-1
- Update to 3.7.5

* Thu Jan 03 2013 Debarshi Ray <rishi@fedoraproject.org> - 3.7.2-1
- Update to 3.7.2

* Fri Nov 09 2012 Kalev Lember <kalevlember@gmail.com> - 3.7.1-1
- Update to 3.7.1

* Tue Oct 16 2012 Kalev Lember <kalevlember@gmail.com> - 3.6.1-1
- Update to 3.6.1

* Wed Sep 26 2012 Matthias Clasen <mclasen@redhat.com> - 3.6.0-1
- Update to 3.6.0

* Wed Sep 19 2012 Richard Hughes <hughsient@gmail.com> - 3.5.92-1
- Update to 3.5.92

* Tue Sep 04 2012 Richard Hughes <hughsient@gmail.com> - 3.5.91-1
- Update to 3.5.91

* Tue Aug 21 2012 Richard Hughes <hughsient@gmail.com> - 3.5.90-1
- Update to 3.5.90

* Fri Jul 27 2012 Fedora Release Engineering <rel-eng@lists.fedoraproject.org> - 3.5.4-2
- Rebuilt for https://fedoraproject.org/wiki/Fedora_18_Mass_Rebuild

* Tue Jul 17 2012 Richard Hughes <hughsient@gmail.com> - 3.5.4-1
- Update to 3.5.4

* Mon Apr 16 2012 Richard Hughes <hughsient@gmail.com> - 3.4.1-1
- Update to 3.4.1

* Thu Apr 12 2012 Kalev Lember <kalevlember@gmail.com> - 3.4.0-2
- Added self-obsoletes to assist with seahorse-sharing package split

* Mon Mar 26 2012 Debarshi Ray <rishi@fedoraproject.org> - 3.4.0-1
- Update to 3.4.0

* Wed Mar 21 2012 Kalev Lember <kalevlember@gmail.com> - 3.3.92-1
- Update to 3.3.92

* Thu Mar 15 2012 Matthias Clasen <mclasen@redhat.com> - 3.3.91-1
- Update to 3.3.91

* Tue Feb 28 2012 Ray Strode <rstrode@redhat.com> 3.3.5-2
- Drop fedora- vendor prefix

* Tue Feb  6 2012 Matthias Clasen <mclasen@redhat.com> - 3.3.5-1
- Update to 3.3.5

* Tue Jan 17 2012 Matthias Clasen <mclasen@redhat.com> - 3.3.4-1
- Update to 3.3.4

* Sat Jan 14 2012 Fedora Release Engineering <rel-eng@lists.fedoraproject.org> - 3.3.3-2
- Rebuilt for https://fedoraproject.org/wiki/Fedora_17_Mass_Rebuild

* Wed Dec 21 2011 Matthias Clasen <mclasen@redhat.com> - 3.3.3-1
- Update to 3.3.3

* Wed Nov  2 2011 Matthias Clasen <mclasen@redhat.com> - 3.3.1-1
- Update to 3.3.1

* Wed Oct 26 2011 Fedora Release Engineering <rel-eng@lists.fedoraproject.org> - 3.2.1-2
- Rebuilt for glibc bug#747377

* Wed Oct 19 2011 Matthias Clasen <mclasen@redhat.com> - 3.2.1-1
- Update to 3.2.1

* Tue Sep 27 2011 Ray <rstrode@redhat.com> - 3.2.0-1
- Update to 3.2.0

* Tue Sep 20 2011 Kalev Lember <kalevlember@gmail.com> 3.1.92-1
- Update to 3.1.92

* Wed Sep 07 2011 Kalev Lember <kalevlember@gmail.com> 3.1.91-1
- Update to 3.1.91

* Wed Aug 31 2011 Kalev Lember <kalevlember@gmail.com> 3.1.90-1
- Update to 3.1.90
- Remove and obsolete seahorse-devel
- Switch to gsettings and obsolete the gconf schema

* Mon Jul 23 2011 Matthew Barnes <mbarnes@redhat.com> 3.1.4-1
- Update to 3.1.4

* Mon May  9 2011 Tomas Bzatek <tbzatek@redhat.com> 3.1.1-1
- Update to 3.1.1

* Mon Apr 25 2011 Matthias Clasen <mclasen@redhat.com> 3.0.1-1
- Update to 3.0.1

* Thu Apr  7 2011 Christopher Aillon <caillon@redhat.com> 3.0.0-1
- Update to 3.0.0

* Fri Mar 25 2011 Matthias Clasen <mclasen@redhat.com> 2.91.93-1
- Update to 2.91.93

* Mon Mar 21 2011 Matthias Clasen <mclasen@redhat.com> 2.91.92-1
- Update to 2.91.92

* Tue Mar  8 2011 Matthias Clasen <mclasen@redhat.com> 2.91.91-1
- Update to 2.91.91

* Fri Feb 11 2011 Matthias Clasen <mclasen@redhat.com> 2.91.4-5
- Rebuild against newer gtk

* Wed Feb 09 2011 Fedora Release Engineering <rel-eng@lists.fedoraproject.org> - 2.91.4-4
- Rebuilt for https://fedoraproject.org/wiki/Fedora_15_Mass_Rebuild

* Wed Feb  2 2011 Matthias Clasen <mclasen@redhat.com> 2.91.4-3
- Rebuild against newer gtk

* Sun Jan  9 2011 Matthias Clasen <mclasen@redhat.com> 2.91.4-2
- Rebuild against newer gtk3

* Mon Jan  3 2011 Tomas Bzatek <tbzatek@redhat.com> 2.91.4-1
- Update to 2.91.4

* Fri Dec  3 2010 Matthias Clasen <mclasen@redhat.com> 2.91.2-2
- Rebuild against new gtk

* Tue Nov  9 2010 Tomas Bzatek <tbzatek@redhat.com> 2.91.2-1
- Update to 2.91.2

* Wed Nov  3 2010 Matthias Clasen <mclasen@redhat.com> 2.91.2-0.1.gitc548f3b
- git snapshot
- build against libnotify 0.7.0

* Tue Nov  2 2010 Matthias Clasen <mclasen@redhat.com> 2.91.1.1-1
- Update to 2.91.1.1

* Mon Oct 18 2010 Tomas Bzatek <tbzatek@redhat.com> 2.91.1-1
- Update to 2.91.1

* Wed Sep 29 2010 Tomas Bzatek <tbzatek@redhat.com> 2.32.0-1
- Update to 2.32.0

* Tue Sep 21 2010 Matthias Clasen <mclasen@redhat.com> - 2.31.91-2
- Rebuild against newer gobject-introspection

* Tue Aug 31 2010 Matthias Clasen <mclasen@redhat.com> - 2.31.91-1
- Update to 2.31.91

* Thu Jul 15 2010 Colin Walters <walters@verbum.org> - 2.30.1-3
- Rebuild with new gobject-introspection

* Tue May 04 2010 Rex Dieter <rdieter@fedoraproject.org> 2.30.1-2
- Requires: pinentry-gui (#587328)

* Tue Apr 27 2010 Tomas Bzatek <tbzatek@redhat.com> 2.30.1-1
- Update to 2.30.1

* Mon Apr 19 2010 Rahul Sundaram <sundaram@fedoraproject.org> 2.30.0-2
- Fix description to mention keyring manager
- Resolves rhbz#536945

* Tue Mar 30 2010 Matthias Clasen <mclasen@redhat.com> 2.30.0-1
- Update to 2.30.0

* Mon Feb 22 2010 Tomas Bzatek <tbzatek@redhat.com> 2.29.91-1
- Update to 2.29.91

* Tue Feb  9 2010 Tomas Bzatek <tbzatek@redhat.com> 2.29.90-1
- Update to 2.29.90
- Removed daemon autostart file (upstream)

* Fri Jan  8 2010 Tomas Bzatek <tbzatek@redhat.com> 2.29.4-2
- Fix bad usage of g_strconcat: missing NULL (#553647)

* Thu Jan  7 2010 Tomas Bzatek <tbzatek@redhat.com> 2.29.4-1
- Update to 2.29.4

* Mon Dec 14 2009 Matthias Clasen <mclasen@redhat.com> 2.29.3-2
- Fix a wrong use of gdk_property_get that can lead to crashes

* Mon Nov 30 2009 Tomas Bzatek <tbzatek@redhat.com> 2.29.3-1
- Update to 2.29.3

* Mon Nov  2 2009 Tomas Bzatek <tbzatek@redhat.com> 2.29.1-1
- Update to 2.29.1

* Tue Sep 22 2009 Tomas Bzatek <tbzatek@redhat.com> 2.28.0-1
- Update to 2.28.0

* Mon Sep 14 2009 Matthias Clasen <mclasen@redhat.com> - 2.27.92-1
- Update to 2.27.92

* Wed Aug 26 2009 Matthias Clasen <mclasen@redhat.com> - 2.27.90-2
- Make seahorse respect the button-images setting

* Tue Aug 11 2009 Matthias Clasen <mclasen@redhat.com> - 2.27.90-1
- Update to 2.27.90

* Thu Aug  6 2009 Matthias Clasen <mclasen@redhat.com> - 2.27.5-2
- Bring the password tab back

* Tue Jul 28 2009 Matthias Clasen <mclasen@redhat.com> - 2.27.5-1
- Update to 2.27.5

* Mon Jul 27 2009 Matthias Clasen <mclasen@redhat.com> - 2.27.1-4
- Drop unneeded direct deps

* Sun Jul 26 2009 Fedora Release Engineering <rel-eng@lists.fedoraproject.org> - 2.27.1-3
- Rebuilt for https://fedoraproject.org/wiki/Fedora_12_Mass_Rebuild

* Mon Jun  1 2009 Tomas Bzatek <tbzatek@redhat.com> 2.27.1-2
- Require pinentry-gtk (#474419)

* Mon May  4 2009 Tomas Bzatek <tbzatek@redhat.com> 2.27.1-1
- Update to 2.27.1

* Sun Apr 12 2009 Matthias Clasen <mclasen@redhat.com> 2.26.1-1
- Update to 2.26.1
- See http://download.gnome.org/sources/seahorse/2.26/seahorse-2.26.1.news

* Fri Apr 10 2009 Matthias Clasen <mclasen@redhat.com> 2.26.0-2
- Fix directory ownership

* Mon Mar 16 2009 Tomas Bzatek <tbzatek@redhat.com> 2.26.0-1
- Update to 2.26.0

* Mon Mar  2 2009 Tomas Bzatek <tbzatek@redhat.com> 2.25.92-1
- Update to 2.25.92

* Wed Feb 25 2009 Fedora Release Engineering <rel-eng@lists.fedoraproject.org> - 2.25.91-2
- Rebuilt for https://fedoraproject.org/wiki/Fedora_11_Mass_Rebuild

* Sat Feb 14 2009 Matthias Clasen <mclasen@redhat.com> 2.25.91-1
- Update to 2.25.91

* Tue Feb  3 2009 Matthias Clasen <mclasen@redhat.com> 2.25.90-1
- Update to 2.25.90

* Wed Jan  7 2009 Matthias Clasen <mclasen@redhat.com> 2.25.4-1
- Update to 2.25.4

* Mon Dec 22 2008 Tomas Bzatek <tbzatek@redhat.com> 2.25.3-1
- Update to 2.25.3

* Tue Dec  2 2008 Matthias Clasen <mclasen@redhat.com> 2.25.1-3
- Rebuild for pkg-config provides

* Mon Dec  1 2008 Tomas Bzatek <tbzatek@redhat.com> 2.25.1-2
- Mark Seahorse as an official replacement for gnome-keyring-manager

* Thu Nov 13 2008 Matthias Clasen <mclasen@redhat.com> 2.25.1-1
- Update to 2.25.1

* Sun Oct 19 2008 Matthias Clasen <mclasen@redhat.com> 2.24.1-1
- Update to 2.24.1

* Thu Oct  9 2008 Matthias Clasen <mclasen@redhat.com> 2.24.0-3
- Save some space

* Sun Sep 21 2008 Matthias Clasen <mclasen@redhat.com> 2.24.0-2
- Update to 2.24.0

* Sun Sep  7 2008 Matthias Clasen <mclasen@redhat.com> 2.23.92-1
- Update to 2.23.92

* Thu Sep  4 2008 Matthias Clasen <mclasen@redhat.com> 2.23.91-1
- Update to 2.23.91

* Sat Aug 30 2008 Michel Salim <salimma@fedoraproject.org> 2.23.90-2
- Patch configure to detect gpg2 binary

* Sat Aug 23 2008 Matthias Clasen <mclasen@redhat.com> 2.23.90-1
- Update to 2.23.90

* Tue Aug  5 2008 Matthias Clasen <mclasen@redhat.com> 2.23.6-1
- Update to 2.23.6
- Split off a -devel package

* Tue Jul 22 2008 Matthias Clasen <mclasen@redhat.com> 2.23.5-1
- Update to 2.23.5

* Mon Apr  7 2008 Matthias Clasen <mclasen@redhat.com> 2.22.1-1
- Update to 2.22.1

* Mon Mar 10 2008 Matthias Clasen <mclasen@redhat.com> 2.22.0-1
- Update to 2.22.0

* Tue Feb 26 2008 Matthias Clasen <mclasen@redhat.com> 2.21.92-1
- Update to 2.21.92

* Fri Feb 15 2008 Matthias Clasen <mclasen@redhat.com> 2.21.90-2
- Rebuild

* Tue Jan 29 2008 Seth Vidal <skvidal at fedoraproject.org> 2.21.90-1
- 2.21.90
- rebuild for new libsoup


* Mon Jan  7 2008 Seth Vidal <skvidal at fedoraproject.org> 2.21.4-2
- drop in seahorse-agent.sh to xinit - closes bug 427466 but will mean
  that seahorse agent will start if it is installed - even on kde or xfce
  desktops :(

* Thu Jan  3 2008 Seth Vidal <skvidal at fedoraproject.org> 2.21.4-1
- upgrade to 2.21.4


* Sat Dec  1 2007 Matt Domsch <mdomsch at fedoraproject.org> 2.21.3-1
- upgrade to 2.21.3
- enable avahi integration
- rpmlint cleanups: remove rpath, unneeded .so, tag config files

* Wed Aug 22 2007 Seth Vidal <skvidal at fedoraproject.org>
- fix license tag
- rebuild for fun!

* Fri Jul 20 2007 Seth Vidal <skvidal at fedoraproject.org>
- disable gedit plugin in rawhide, for now :(

* Tue Jun 26 2007 Seth Vidal <skvidal at fedoraproject.org>
- update to 1.0.1

* Sun Aug 13 2006 Seth Vidal <skvidal at linux.duke.edu>
- re-enable gedit
- update to 0.8.1

* Tue Mar  7 2006 Seth Vidal <skvidal at linux.duke.edu>
- added openldap-devel buildreq to hopefully close bug # 184124

* Thu Feb 23 2006 Seth Vidal <skvidal at linux.duke.edu>
- Patch from John Thacker for rh bug #182694 


* Mon Jan 16 2006 Seth Vidal <skvidal at linux.duke.edu> - 0.8-2
- added configure patch for it to build
- disable gedit plugins until seahorse gets fixed to work with gedit 2.13+

* Wed Oct 26 2005 Seth Vidal <skvidal@phy.duke.edu> - 0.8-1
- 0.8

* Thu Jul 28 2005 Seth Vidal <skvidal@phy.duke.edu> - 0.7.9-1
- 0.7.9

* Wed May 25 2005 Jeremy Katz <katzj@redhat.com> - 0.7.7-3
- make sure all files are included
- BR nautilus-devel

* Sun May 22 2005 Jeremy Katz <katzj@redhat.com> - 0.7.7-2
- rebuild on all arches

* Thu May  5 2005 Seth Vidal <skvidal@phy.duke.edu> 0.7.7-1
- 0.7.7

* Tue Apr 19 2005 Seth Vidal <skvidal at phy.duke.edu> 0.7.6-4
- something innocuous to test on


* Fri Apr  7 2005 Michael Schwendt <mschwendt[AT]users.sf.net>
- rebuilt

* Fri Feb 25 2005 Phillip Compton <pcompton[AT]proteinmedia.com> 0.7.6-2
- desktop entry fixes.

* Fri Feb 25 2005 Phillip Compton <pcompton[AT]proteinmedia.com> 0.7.6-1
- 0.7.6.

* Mon Nov 09 2003 Phillip Compton <pcompton[AT]proteinmedia.com> 0:0.7.3-0.fdr.5
- BuildReq scrollkeeper.

* Wed Oct 22 2003 Phillip Compton <pcompton[AT]proteinmedia.com> 0:0.7.3-0.fdr.4
- Uncommented .la removal.

* Sun Sep 21 2003 Phillip Compton <pcompton[AT]proteinmedia.com> 0:0.7.3-0.fdr.3
- Grabbed new copy os source from upstream.
- Fixed path on Source0, to allow direct download.
- BuildReq desktop-file-utils.

* Sun Sep 21 2003 Phillip Compton <pcompton[AT]proteinmedia.com> 0:0.7.3-0.fdr.2
- Fixed file permission on source tarball.
- Fixed Group.
- Removed aesthetic comments.
- Brought more in line with current spec template.

* Sun Aug 17 2003 Phillip Compton <pcompton[AT]proteinmedia.com> 0:0.7.3-0.fdr.1
- Fedorification.
- Added path to Source0.
- Added URL.
- buildroot -> RPM_BUILD_ROOT.
- BuildReq libgnomeui-devel, eel2-devel, gpgme03-devel.
- BuildReq gettext.
- post Req GConf2.
- post/postun Req scrollkeeper.
- .la/.a removal.
- cosmetic changes.

* Fri May 02 2003 Matthew Hall <matt@ecsc.co.uk> 0.7.3-1
- 0.7.3 Release

* Wed Apr 23 2003 Matthew Hall <matt@ecsc.co.uk> 0.7.1-3
- Rebuilt against gpgme 0.3.15

* Sat Apr 12 2003 Matthew Hall <matt@ecsc.co.uk> 0.7.1-2
- RedHat 9 Rebuild

* Sun Jan 26 2003 Matthew Hall <matt@ecsc.co.uk>
- New Spec File

