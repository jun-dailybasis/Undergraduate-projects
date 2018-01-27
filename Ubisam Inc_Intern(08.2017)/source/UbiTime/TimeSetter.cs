using System;
using System.Windows;
using System.Runtime.InteropServices;
using System.Net.Sockets;
using System.Globalization;
using System.IO;
using System.Security.Principal;


namespace UbisamIntern_Project.UbiTime
{
    /// <summary>
    /// Creator : 방준영 (iris0126@kut.ac.kr)
    /// Create : 2017.08.15
    /// LastUpdate : 2017.08.17
    /// Description : 서버로 부터 Global Time을 받아와 OS 시스템 시간 설정
    ///               시스템 시간을 설정하기 위해 관리자 권한 필요
    ///</summary> 
    public partial class TimeSetter
    {
        /// <summary>
        /// time.nist.gov 서버로부터 시간을 받아오기 위한 구조체와 Dll을 Import
        /// </summary>
        [DllImport("kernel32.dll")]
        internal static extern bool SetLocalTime(ref SYSTEMTIME time);
        [StructLayoutAttribute(LayoutKind.Sequential)]
        public struct SYSTEMTIME
        {
            public ushort wYear;
            public ushort wMonth;
            public ushort wDayOfWeek;
            public ushort wDay;
            public ushort wHour;
            public ushort wMinute;
            public ushort wSecond;
            public ushort wMilliseconds;
        }
        /// <summary>
        /// 생성자
        /// </summary>
        public TimeSetter() { }

        /// <summary>
        /// 관리자 권한 유무 확인
        /// </summary>
        /// <returns></returns>
        public static bool IsAdministrator()
        {
            var identity = WindowsIdentity.GetCurrent();
            var principal = new WindowsPrincipal(identity);
            return principal.IsInRole(WindowsBuiltInRole.Administrator);
        }
        /// <summary>
        /// 서버로 부터 Global 시간을 받아 OS시간 설정
        /// </summary>
        public void doTimeSync()
        {
            if (IsAdministrator())
            {
                SYSTEMTIME st;

                var client = new TcpClient("time.nist.gov", 13);

                using (var streamReader = new StreamReader(client.GetStream()))
                {

                    String response = streamReader.ReadToEnd();
                    if (response != "")
                    {
                        var utcDateTimeString = response.Substring(7, 17);
                        var localDateTime = DateTime.ParseExact(utcDateTimeString, "yy-MM-dd HH:mm:ss", CultureInfo.InvariantCulture, DateTimeStyles.AssumeUniversal);
                        st.wYear = (ushort)localDateTime.Year;
                        st.wMonth = (ushort)localDateTime.Month;
                        st.wDayOfWeek = (ushort)localDateTime.DayOfWeek;
                        st.wDay = (ushort)localDateTime.Day;
                        st.wHour = (ushort)localDateTime.Hour;
                        st.wMinute = (ushort)localDateTime.Minute;
                        st.wSecond = (ushort)localDateTime.Second;
                        st.wMilliseconds = (ushort)localDateTime.Millisecond;
                        SetLocalTime(ref st);

                    }
                    else throw new SocketException();
                }
            }
            else throw new UnauthorizedAccessException();
        }
    }
}
