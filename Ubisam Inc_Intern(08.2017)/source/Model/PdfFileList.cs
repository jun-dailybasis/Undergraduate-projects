using System.Linq;
using System.Collections.ObjectModel;

namespace UbisamIntern_Project.Model
{
    /// <summary>
    /// Creator : 이도형(esrenll@gmail.com), 방준영 (iris0126@kut.ac.kr)
    /// Create : 2017.08.05
    /// LastUpdate : 2017.08.10
    /// Description : Pdf포함 파일들의 정보를 저장하는 Collection클래스
    /// </summary>
    public class PdfFileList : ObservableCollection<PdfFileInfo> { }
    public class PdfFileInfo
    {
        //파일의 이름만 저장할 수 있도록 생성자 부분에서 제어 하기 위해 showNameOnly 멤버 변수 생성
        //파일의 이름과 경로를 저장 하기 위핸 멤버변수 생성
        bool showNameOnly = true;
        string name, path;
        /// <summary>
        /// 생성자
        /// </summary>
        public PdfFileInfo(string filePath, bool showNameOnly)
        {
            Path = filePath;
            Name = Path.Split('\\').Last();
            this.showNameOnly = showNameOnly;
        }
        /// <summary>
        /// Getter, Setter
        /// </summary>
        public string Name
        {
            get { return name; }
            set
            {
                name = value;
                path = System.IO.Path.GetDirectoryName(path) + @"\" + name;
            }
        }

        public string Path
        {
            get { return path; }
            set
            {
                path = value;
                name = System.IO.Path.GetFileName(path);
            }
        }
        /// <summary>
        /// showNameOnly 변수 상태에 따라 파일의 이름, 경로 출력을 선택
        /// </summary>
        /// <returns></returns>
        public override string ToString()
        {
            return showNameOnly ? Name : Path;
        }
    }
}