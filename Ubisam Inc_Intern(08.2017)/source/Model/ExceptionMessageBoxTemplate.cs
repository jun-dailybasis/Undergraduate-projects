using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;
using System.Windows;

namespace UbisamIntern_Project.Model
{

    /// <summary>
    /// Creator : 이도형 (esrenll@gmail.com)
    /// Create : 2017.08.18
    /// LastUpdate : 2017.08.30 (메시지 수정 및 추가)
    /// Description : 특정 예외에 따라 보여주는 메시지박스 템플릿 정적 클래스
    /// </summary>
    static class ExceptionMessageBoxTemplate
    {
        /// <summary>
        /// Ghostscript 사용 중 DllNotFoundException 발생 시 호출할 메시지박스(gsdll32.dll 문제)
        /// </summary>
        /// <param name="e"></param>
        public static void showGhostscriptDllNotFound(DllNotFoundException e)
        {
            MessageBox.Show("No gsdll32.dll was found. This function requires gsdll32.dll file. put the gsdll32.dll in execution directory."
                + "\n\n" + e.GetType().ToString() + "\n" + e.Message);
        }

        /// <summary>
        /// Ghostscript 사용 중 영어가 아닌 경로를 들어갔을 때 호출할 메시지 박스
        /// </summary>
        /// <param name="e"></param>
        public static void showGhostscriptOnlySupportedEnglishPath(Ghostscript.NET.GhostscriptException e)
        {
            MessageBox.Show("PDF rasterize function(Ghostscript) only supports paths in English. Please try again with English path."
                + "\n\n" + e.GetType().ToString() + "\n" + e.Message);
        }

        /// <summary>
        /// 관리자 권한이 없는 경우 호출할 메시지박스
        /// </summary>
        /// <param name="e"></param>
        public static void showUnauthorizedAccessException(UnauthorizedAccessException e)
        {
            MessageBox.Show("You can not access the file without administrator permission.\n"
                + "Try another directory or run the program again with administrator permisson."
                + "\n\n" + e.GetType().ToString() + "\n" + e.Message);
        }

        /// <summary>
        /// MS Office가 설치되지 않은 경우 호출할 메시지박스
        /// COMException이 해당
        /// </summary>
        /// <param name="e"></param>
        public static void showMSOfficeNotInstalledException(COMException e)
        {
            MessageBox.Show("We cannot find MS Office. MS Office is required to use this function.\n"
                + "Install MS Office and try again."
                + "\n\n" + e.GetType().ToString() + "\n" + e.Message);
        }
    }
}
