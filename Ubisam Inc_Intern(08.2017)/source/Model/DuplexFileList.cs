using System.Linq;
using System.Collections.ObjectModel;

namespace UbisamIntern_Project.Model
{

    /// <summary>
    /// Creator : 이도형(esrenll@gmail.com)
    /// Create : 2017.08.30
    /// LastUpdate : 2017.08.30
    /// Description : Duplex Print에서 DataGrid의 리스트를 저장하는 Collection클래스
    /// </summary>
    public class DuplexFileList : ObservableCollection<DuplexFileInfo> { }

    public class DuplexFileInfo
    {
        public string Name { get; set; }
        public string Page { get; set; }
        public string Modified { get; set; }
        public string Size { get; set; }
    }
}