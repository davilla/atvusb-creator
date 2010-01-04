Injector DLL
------------

Notes: Used for injecting boot.efi into software image.
	
	Following is harcoded:

	- Offset Number = 2437120
	- Basefile = ImageFile.img	
	- InFile = boot.efi

Exposed to atv-win-3.0 with: 

_declspec(dllexport) int newefi()

Used in atv-win-3.0 with:

<DllImport("injectordll.dll")> _
Public Shared Function newefi() As Boolean

Boolean return codes:

False - successful (proceedure not skipped)
True - error (proceedure skipped)

-- Sam Nazarko (4/01/2010)