# Tweaks for SideLoaded Apps

non jailbroken device tweaks for ( WhatsApp - Snapchat - Instagram )

WhatsApp
------

* Freeze Last Seen
* Disable Read Mark ( blue check )
* Support IPAD

Snapchat
------

* Save Snaps ( images and videos )

Instagram
------

* save/share photos
* save/share videos
* share comments

How to use
------

* load it inside the app binary using [optool](https://github.com/alexzielenski/optool)
* sign the dylib using 
```
codesign -fs "iPhone Developer: XXXXXX"
```
* copy the dylib inside the app bundle path
* sign the app ipa file using [iOS App Signer](https://github.com/DanTheMan827/ios-app-signer) or [AppSignerCMD](https://github.com/iMokhles/AppSignerCMD) 

* after that install the app using IPAInstaller [Windows](https://github.com/iMokhles/IPAInstaller-Windows/releases/download/1.1/IPAInstaller.exe)  - [Mac](https://github.com/iMokhles/IPAInstaller-Mac/releases/download/1.0/IPAInstaller-1.0.zip)


#MIT License

	Copyright (c) 2016 iMokhles (Mokhlas Hussien). All rights reserved.

	Permission is hereby granted, free of charge, to any person obtaining a
	copy of this software and associated documentation files (the "Software"),
	to deal in the Software without restriction, including
	without limitation the rights to use, copy, modify, merge, publish,
	distribute, sublicense, and/or sell copies of the Software, and to
	permit persons to whom the Software is furnished to do so, subject to
	the following conditions:

	The above copyright notice and this permission notice shall be included
	in all copies or substantial portions of the Software.

	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
	OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
	MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
	IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
	CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
	TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
	SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.