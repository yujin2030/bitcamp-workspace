using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _0930_실기시험11
{
    delegate void DelCount(int c); //델리게이트 선언

    class bookstore
    {
        List<book> booklist = new List<book>();
        public DelCount c = null;   //델리게이트 초기화


    //3.저장
     public void insert(string n, int p)
    {
        book bo = new book(n, p);
        booklist.Add(bo);
    }

    //4. 전체출력
    public void PrintAll()
    {
        foreach(book b in booklist)
        {
            Console.WriteLine(b);
        }
    }

    //5. 검색기능
    public void select(string n)
        {
            foreach (book b in booklist)
            {
                if (b.Name.Equals(n))
                {
                    Console.Write(b);
                    return;
                }
                throw new Exception ("일치하는 책이 없습니다.");

            }
        }       

    //6. 수정기능
    public void update(string n, int cou)
        {
            foreach (book b in booklist)
            {
                if (b.Name.Equals(n))
                {
                    b.UpdateSal(cou);
                    c(b.Salcount);   //델리게이트
                    return;
                }
                throw new Exception("일치하는 책이 없습니다.");

            }
        }

        //7. 삭제기능
        public void delete(string n)
        {
            for (int i = 0; i < booklist.Count; i++)
            {
                book mem = booklist[i];
                if (mem.Name.Equals(n))
                {
                    booklist.Remove(mem);
                    return;
                }
            }
            throw new Exception("삭제할 책이 없습니다.");
        }
    }
}
