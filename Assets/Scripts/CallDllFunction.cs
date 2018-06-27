using UnityEngine;
using System;
using System.Runtime.InteropServices;

namespace NativePluginExample
{

    public class CallDllFunction : MonoBehaviour
    {
        void Update()
        {
            Debug.Log(Lib.GetNumber());

            //float[] inPoints, outPoints;

            double[] inPoints = new double[8];
            double[] outPoints = new double[8];
            double[] homography = new double[9];

            inPoints[0] = 0;
            inPoints[1] = 0;
            inPoints[2] = 1;
            inPoints[3] = 0;
            inPoints[4] = 1;
            inPoints[5] = 1;
            inPoints[6] = 0;
            inPoints[7] = 1;

            outPoints[0] = 0;
            outPoints[1] = 0;
            outPoints[2] = 2;
            outPoints[3] = 0;
            outPoints[4] = 2;
            outPoints[5] = 2;
            outPoints[6] = 0;
            outPoints[7] = 2;

            homography[0] = 0;
            homography[1] = 0;
            homography[2] = 1;
            homography[3] = 0;
            homography[4] = 1;
            homography[5] = 1;
            homography[6] = 0;
            homography[7] = 1;
            homography[8] = 0;

            double[] p1 = new double[3];
            double[] p2 = new double[3];
            p1[0] = 0.5f;
            p1[1] = 0.5f;
            p1[2] = 1.0f;
            p2[0] = 0.0f;
            p2[1] = 0.0f;
            p1[2] = 1.0f;

            IntPtr src = Marshal.AllocHGlobal(inPoints.Length * sizeof(double));
            Marshal.Copy(inPoints, 0, src, inPoints.Length);

            IntPtr dst = Marshal.AllocHGlobal(outPoints.Length * sizeof(double));
            Marshal.Copy(outPoints, 0, dst, outPoints.Length);

            IntPtr h = Marshal.AllocHGlobal(homography.Length * sizeof(double));
            Marshal.Copy(homography, 0, h, homography.Length);

            Debug.Log(Lib.CalcHomography(src, dst, h));
            Debug.Log(h);

            IntPtr srcPoint = Marshal.AllocHGlobal(p1.Length * sizeof(double));
            Marshal.Copy(p1, 0, srcPoint, p1.Length);

            IntPtr dstPoint = Marshal.AllocHGlobal(p2.Length * sizeof(double));
            Marshal.Copy(p2, 0, dstPoint, p2.Length);

            Debug.Log(Lib.CalcHomographyPoint(srcPoint, dstPoint, src, dst));

            double[] array = new double[p2.Length];
            Marshal.Copy(dstPoint, array, 0, p2.Length);

            Debug.Log(array[0].ToString() + ", " + array[1].ToString() + ", " + array[2].ToString() + ", " );
        }
    }

}