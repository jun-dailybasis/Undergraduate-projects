using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace UbisamIntern_Project.Model
{
    /// <summary>
    /// Creator : 이도형 (esrenll@gmail.com)
    /// Create : 2017.08.18
    /// LastUpdate : 2017.08.21
    /// Description : PDF Print 진행경과 표시를 위한 클래스
    /// Usage : 1. 객체 생성
    ///         2. 각 멤버에 대해 update 될 시 작동할 delegate 함수(UI 변경 등) 등록
    ///         3. 작업 클래스에 등록, 변수 변경
    /// </summary>
    public class ProgressModel
    {
        // 진행 경과에 대한 정보
        private string fileName = "";
        private long totalFileSize = 0;
        private long currentFileSize = 0;
        private int totalFileNum = 1;
        private int currentFileNum = 1;
        private int totalPageNum = 1;
        private int currentPageNum = 1;
        private long progressedSize = 0;

        // updateXXX 가 호출됐을 시 호출할 델리게이트
        public delegate void delegateUpdate();
        private delegateUpdate delegateUpdateFileName;
        private delegateUpdate delegateUpdateTotalFileSize;
        private delegateUpdate delegateUpdateFileSize;
        private delegateUpdate delegateUpdateTotalFileNum;
        private delegateUpdate delegateUpdateCurrentFileNum;
        private delegateUpdate delegateUpdateTotalPageNum;
        private delegateUpdate delegateUpdateCurrentPageNum;
        private delegateUpdate delegateUpdateProgressedSize;

        // 델리게이트에 추가
        public void addDelegateUpdateFileName(delegateUpdate du) { delegateUpdateFileName += du; }
        public void addDelegateUpdateTotalFileSize(delegateUpdate du) { delegateUpdateTotalFileSize += du; }
        public void addDelegateUpdateFileSize(delegateUpdate du) { delegateUpdateFileSize += du; }
        public void addDelegateUpdateTotalFileNum(delegateUpdate du) { delegateUpdateTotalFileNum += du; }
        public void addDelegateUpdateCurrentFileNum(delegateUpdate du) { delegateUpdateCurrentFileNum += du; }
        public void addDelegateUpdateTotalPageNum(delegateUpdate du) { delegateUpdateTotalPageNum += du; }
        public void addDelegateUpdateCurrentPageNum(delegateUpdate du) { delegateUpdateCurrentPageNum += du; }
        public void addDelegateUpdateProgressedSize(delegateUpdate du) { delegateUpdateProgressedSize += du; }

        // 정보를 update 하는 메소드
        // update한 경우 해당 델리게이트 실행
        public string FileName
        {
            get { return fileName; }
            set
            {
                fileName = value;
                delegateUpdateFileName?.Invoke();
            }
        }
        public long TotalFileSize
        {
            get { return totalFileSize; }
            set
            {
                totalFileSize = value;
                delegateUpdateTotalFileSize?.Invoke();
            }
        }
        public long CurrentFileSize
        {
            get { return currentFileSize; }
            set
            {
                currentFileSize = value;
                delegateUpdateFileSize?.Invoke();
            }
        }
        public int TotalFileNum
        {
            get { return totalFileNum; }
            set
            {
                totalFileNum = value;
                delegateUpdateTotalFileNum?.Invoke();
            }
        }
        public int CurrentFileNum
        {
            get { return currentFileNum; }
            set
            {
                currentFileNum = value;
                delegateUpdateCurrentFileNum?.Invoke();
            }
        }
        public int TotalPageNum
        {
            get { return totalPageNum; }
            set
            {
                totalPageNum = value;
                delegateUpdateTotalPageNum?.Invoke();
            }
        }
        public int CurrentPageNum
        {
            get { return currentPageNum; }
            set
            {
                currentPageNum = value;
                delegateUpdateCurrentPageNum?.Invoke();
            }
        }
        public long ProgressedSize
        {
            get { return progressedSize; }
            set
            {
                progressedSize = value;
                delegateUpdateProgressedSize?.Invoke();
            }
        }
    }
}
