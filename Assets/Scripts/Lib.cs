using System.Runtime.InteropServices;
using System;

namespace NativePluginExample
{

    public static class Lib
    {
        [DllImport("HomographyPoint")]
        public static extern int GetNumber();

        [DllImport("HomographyPoint")]
        public static extern int CalcHomography(IntPtr src, IntPtr dst, IntPtr homography);

        [DllImport("HomographyPoint")]
        public static extern int CalcHomographyPoint(IntPtr input, IntPtr output, IntPtr src, IntPtr dst);


        //CalcHomographyPoint(const double* input, double* output, const double* src, const double* dst)

        //UNITY_INTERFACE_EXPORT int UNITY_INTERFACE_API CalcHomography(const double* src, const double* dst )
    }

}