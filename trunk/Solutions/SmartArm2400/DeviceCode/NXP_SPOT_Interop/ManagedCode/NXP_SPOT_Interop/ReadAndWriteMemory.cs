using System;
using System.Runtime.CompilerServices;

namespace NXP.SPOT.Interop
{
    public static class ReadAndWriteMemory
    {
        [MethodImpl(MethodImplOptions.InternalCall)]
        public extern static uint Read(uint address);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public extern static void Wirte(uint address, uint value);
    }
}
