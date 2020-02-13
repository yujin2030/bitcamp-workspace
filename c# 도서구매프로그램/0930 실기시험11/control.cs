using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _0930_실기시험11
{
    class control
    {
        bookstore store = new bookstore();

        #region 싱글톤
        public static control Instance
        {
            get; private set;
        }

        static control()
        {
            Instance = new control();
        }
        private control()
        {
           store.c = GetCountValue;
        }
        #endregion

        //9. 저장
        public void Cinsert()
        {
            try
            {
                Console.Write("책제목 : ");
                string name = Console.ReadLine();

                Console.Write("가격 : ");
                int price = int.Parse(Console.ReadLine());

                store.insert(name, price);
                Console.WriteLine("저장완료");
            }
            catch(Exception ex)
            {
                Console.WriteLine(ex.Message);
            }
        }

        //10. 전체출력
        public void CPrintAll()
        {
            try
            {
                store.PrintAll();
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.Message);
            }
        }

        //11. 검색기능
        public void Cselect()
        {
            try
            {
                Console.Write("검색할 책 제목: ");
                string name = Console.ReadLine();
                store.select(name);
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.Message);
            }
        }

        //12. 수정기능

        public void Cupdate()
        {
            try
            {
                Console.Write("수정할 책 제목: ");
                string name = Console.ReadLine();
                Console.Write("판매량 : ");
                int count = int.Parse(Console.ReadLine());
                store.update(name, count);
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.Message);
            }
        }
        //13.삭제기능
        public void Cdelete()
        {
            try
            {
                Console.Write("삭제할 책 제목: ");
                string name = Console.ReadLine();
                store.delete(name);
                Console.WriteLine("삭제완료");

            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.Message);
            }
        }

        //18.콜백정의 (델리게이트)
        public void GetCountValue(int c)
        {
            Console.WriteLine("누적판매량 : {0}", c);
        }
    }
}
