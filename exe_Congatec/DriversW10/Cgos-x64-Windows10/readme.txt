==============================================================================
  congatec 32bit/64bit CGOS API for Windows                   DATE: 27.08.2019
==============================================================================


THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER 
DEALINGS IN THE SOFTWARE.


OVERVIEW:
---------

The CGOS (congatec OS) API provides access to congatec specific board
information and features.

The API is compatible and identical across all congatec boards and all 
supported operating systems.

This package includes support for the following operating systems:
	Windows 10 	(64bit)
	
	Signed for following versions:
	Windows 10 1506 and 1511 x64
	Windows 10 1607 x64 (RS1)
	Windows 10 1703 x64 (RS2)
	Windows 10 1709 x64 (RS3)
	Windows 10 1803 x64 (RS4)
	Windows 10 1809 x64 (RS5)
	Windows 10 19H1 x64 
		
The 64bit interface is able to work with native 64bit applications as well as with
32bit applications that run in the WOW64 environment.


INSTALLATION:
-------------

Please run the included InstallCGOS.bat as administrator / from an administrator shell.


USAGE:
------

To use the CGOS Library API functions from a C/C++ project you need to include the
Cgos.h header file (\Cgos\INC\Cgos.h) and link with the matching Cgos.lib import 
library for your OS (\Cgos\32\LIB\Cgos.lib or \Cgos\64\LIB\Cgos.lib).

For CGOS function details and parameters please refer to the Cgos.h header file
and the CGOS API User's Guide available on the congatec web page.
Sample files are provided in source and binary in this package that demonstrate 
some of the CGOS functions (CgosDump, cgosmon).


  (c) 2019, congatec AG 