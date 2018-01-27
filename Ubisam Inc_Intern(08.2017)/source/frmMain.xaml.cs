using System;
using System.Windows;
using System.Windows.Input;
using System.IO;
using System.Runtime.InteropServices;
using System.Net.Sockets;
using System.Globalization;
using UbisamIntern_Project.UbiTime;
using System.Threading;
using System.Drawing;
using ToastNotifications;
using ToastNotifications.Position;

namespace UbisamIntern_Project
{
    /// <summary>
    /// Creator : 손지훈 (jihoon647@naver.com)
    /// Create : 2017.08.16
    /// LastUpdate : 2017.08.30 (토스트 추가)
    /// Description : 8개의 기능 표기
    /// License : MIT (AndroidToast), https://raw.githubusercontent.com/mrousavy/Toast/master/license.txt
    /// </summary>
    public partial class frmMain : Window
    {
        bool firstActivated = true;
        /// <summary>
        /// 생성자 및 컴포넌츠 초기화
        /// 서버(time.nist.gov)로부터 Global Time을 받아 OS타임 설정
        /// 관리자 권한 필요
        /// </summary>
        public frmMain()
        {
            InitializeComponent();
        }


        /// <summary>
        /// 각각의 button 클릭시 동작
        /// button의 맞는 프로젝트 실행
        /// </summary>
        private void btnDuplexPrint_Click(object sender, RoutedEventArgs e)
        {
            new fun1_DuplexPrint().Show();
        }
        private void btnDirListAndPrint_Click(object sender, RoutedEventArgs e)
        {
            new fun2_DirListAndPrint().Show();
        }
        private void btnConverToPDF_Click(object sender, RoutedEventArgs e)
        {
            new fun3_ConvertToPDF().Show();
        }
        private void btnPrintHeader_Click(object sender, RoutedEventArgs e)
        {
            new fun4_PrintHeader().Show();
        }
        private void btnRename_Click(object sender, RoutedEventArgs e)
        {
            new fun5_Rename().Show();
        }
        private void btnRepath_Click(object sender, RoutedEventArgs e)
        {
            new fun6_Repath().Show();
        }
        private void btnSearchByLetter_Click(object sender, RoutedEventArgs e)
        {
            new fun7_SearchByLetter().Show();
        }
        private void btnBatchPrint_Click(object sender, RoutedEventArgs e)
        {
            new fun8_BatchPrint().Show();
        }
        private void btnAppExit_Click(object sender, RoutedEventArgs e)
        {
            Application.Current.Shutdown();
        }
        private void VersionInfo_Click(object sender, RoutedEventArgs e)
        {
            new UbisamIntern_Project.VersionInfo().Show();
        }
        private void help_Click(object sender, RoutedEventArgs e)
        {
            HelpInfo popup = new UbisamIntern_Project.HelpInfo();
            popup.ShowDialog();

        }
        /// <summary>
        /// button의 핫키 설정
        /// 핫키 입력시 각각의 맞는 프로젝트 실행
        /// </summary>
        private void Main_KeyDown(object sender, KeyEventArgs e)
        {

            if (e.Key == Key.D || e.Key == Key.D1)
            {
                new fun1_DuplexPrint().Show();
            }
            else if (e.Key == Key.L || e.Key == Key.D2)
            {
                new fun2_DirListAndPrint().Show();
            }
            else if (e.Key == Key.C || e.Key == Key.D3)
            {
                new fun3_ConvertToPDF().Show();
            }
            else if (e.Key == Key.H || e.Key == Key.D4)
            {
                new fun4_PrintHeader().Show();
            }
            else if (e.Key == Key.N || e.Key == Key.D5)
            {
                new fun5_Rename().Show();
            }
            else if (e.Key == Key.P || e.Key == Key.D6)
            {
                new fun6_Repath().Show();
            }
            else if (e.Key == Key.S || e.Key == Key.D7)
            {
                new fun7_SearchByLetter().Show();
            }
            else if (e.Key == Key.B || e.Key == Key.D8)
            {
                new fun8_BatchPrint().Show();
            }
            else if (e.Key == Key.I)
            {
                new HelpInfo().Show();
            }
            else if (e.Key == Key.V)
            {
                new VersionInfo().Show();
            }


        }

        /// <summary>
        /// 윈도우가 활성화되었을 때 실행되는 코드
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void Window_Activated(object sender, EventArgs e)
        {
            if (firstActivated)
            {

                Dispatcher.Invoke(System.Windows.Threading.DispatcherPriority.Normal, new Action(delegate ()
                {
                    try
                    {
                        new TimeSetter().doTimeSync();
                    }
                    catch (SocketException)
                    {
                        MessageBox.Show("Network is not connected or server no respone.");
                    }
                    catch (UnauthorizedAccessException)
                    {
                        MessageBox.Show("You need administrator privilege to set OS time.");
                    }
                    catch (Exception exception)
                    {
                        MessageBox.Show(exception.GetType().ToString() + "\n\n" + exception.Message);
                    }
                }));
                firstActivated = false;
            }
        }
    }
}
