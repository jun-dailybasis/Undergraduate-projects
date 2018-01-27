using System.Linq;
using System.Collections.ObjectModel;
using System.IO;
using System.Collections.Generic;

namespace UbisamIntern_Project.Model
{
    /// <summary>
    /// Creator : 이도형 (esrenll@gmail.com)
    /// Create : 2017.08.30
    /// LastUpdate : 2017.08.30
    /// Description : 파일과, 파일이 아닌 경우 하위 경로의 파일들을 사용하게 해주는 정적 클래스
    /// </summary>
    static public class FileExplorer
    {
        /// <summary>
        /// 해당 디렉토리 하위의 파일들(하위 디렉토리 포함)을 반환
        /// </summary>
        /// <param name="dir"></param>
        /// <returns></returns>
        static private string[] getSubFiles(string dir)
        {
            if (!File.Exists(dir) && !Directory.Exists(dir)) return null;

            List<string> ret = new List<string>();
            foreach (string file in Directory.GetFileSystemEntries(dir))
            {
                if (File.Exists(file))
                    ret.Add(file);
                else if (Directory.Exists(file))
                {
                    foreach (string subFile in getSubFiles(file))
                        ret.Add(subFile);
                }
            }
            return ret.ToArray();
        }

        /// <summary>
        /// 파일과, 디렉토리의 경우 하위의 파일들(하위 디렉토리 포함)을 반환
        /// </summary>
        /// <param name="files"></param>
        /// <returns></returns>
        static public string[] filesAndInSubDirectoryFiles(string[] files)
        {
            List<string> ret = new List<string>();
            foreach(string file in files)
            {
                if(File.Exists(file))
                    ret.Add(file);
                else if(Directory.Exists(file))
                {
                    foreach (string subFile in getSubFiles(file))
                        ret.Add(subFile);
                }
            }
            return ret.ToArray();
        }
    }
}