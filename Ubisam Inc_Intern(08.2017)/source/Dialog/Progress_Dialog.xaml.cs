using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Shapes;
using System.Windows.Threading;

namespace UbisamIntern_Project
{
    /// <summary>
    /// Creator : 이도형 (esrenll@gmail.com)
    /// Create : 2017.08.18
    /// LastUpdate : 2017.08.21
    /// Description : PrintProgress_Dialog.xaml에 대한 상호 작용 논리
    /// Usage :  1. 객체 생성
    ///          2. ProgressModel을 작업 메소드에 인자로 삽입(PdfPrint.print 혹은 PdfPrint.insertDocument 등)
    ///          3. 작업 메소드에 따라 Show, Close 그리고 ProgressModel 값을 조절
    /// </summary>
    public partial class Progress_Dialog : Window
    {
        /// <summary>
        /// 객체가 만들어진 시간
        /// </summary>
        DateTime createdTime = DateTime.Now;
        /// <summary>
        /// 진행상황을 중계해주는 모델
        /// </summary>
        private Model.ProgressModel progressModel = new Model.ProgressModel();
        /// <summary>
        /// 진행상황을 중계해주는 모델
        /// </summary>
        public Model.ProgressModel ProgressModel
        {
            get { return progressModel; }
        }
        
        
        /// <summary>
        /// 생성자, progressModel에 이벤트 리스너 등록
        /// </summary>
        /// <param name="status"></param>
        public Progress_Dialog(string status)
        {
            InitializeComponent();

            label_Status.Content = status;
            progressModel.addDelegateUpdateFileName(delegate
            {
                label_FileName.Content = progressModel.FileName;
                Dispatcher.Invoke((ThreadStart)(() => { }), DispatcherPriority.ApplicationIdle);
            });
            progressModel.addDelegateUpdateProgressedSize(delegate
            {
                double progress = (double)progressModel.ProgressedSize / progressModel.TotalFileSize;
                double elapsed = DateTime.Now.Subtract(createdTime).TotalSeconds;
                label_RemainTime.Content = String.Format("remain: {0:0.0}s",
                    elapsed * ((double)progressModel.TotalFileSize / progressModel.ProgressedSize - 1.0));
                label_TotalProgress.Content = String.Format("{0:0.00}%", progress * 100.0);
                progressBar.Value = progress * 100.0;
                Dispatcher.Invoke((ThreadStart)(() => { }), DispatcherPriority.ApplicationIdle);
            });
            progressModel.addDelegateUpdateTotalFileNum(delegate
            {
                label_FileProgress.Content = "" +
                    progressModel.CurrentFileNum + "/" + progressModel.TotalFileNum;
                Dispatcher.Invoke((ThreadStart)(() => { }), DispatcherPriority.ApplicationIdle);
            });
            progressModel.addDelegateUpdateCurrentFileNum(delegate
            {
                label_FileProgress.Content = "" +
                    progressModel.CurrentFileNum + "/" + progressModel.TotalFileNum;
                Dispatcher.Invoke((ThreadStart)(() => { }), DispatcherPriority.ApplicationIdle);
            });
            progressModel.addDelegateUpdateTotalPageNum(delegate
            {
                label_PageProgress.Content = "" +
                    progressModel.CurrentPageNum + "/" + progressModel.TotalPageNum;
                Dispatcher.Invoke((ThreadStart)(() => { }), DispatcherPriority.ApplicationIdle);
            });
            progressModel.addDelegateUpdateCurrentPageNum(delegate
            {
                label_PageProgress.Content = "" +
                    progressModel.CurrentPageNum + "/" + progressModel.TotalPageNum;
                Dispatcher.Invoke((ThreadStart)(() => { }), DispatcherPriority.ApplicationIdle);
            });
        }

        /// <summary>
        /// 객체 생성시간 초기화
        /// </summary>
        public void resetCreatedTime()
        {
            createdTime = DateTime.Now;
        }

        /// <summary>
        /// 상태창 내용 변경
        /// </summary>
        /// <param name="status"></param>
        public void resetStatus(string status)
        {
            label_Status.Content = status;
        }
    }
}
