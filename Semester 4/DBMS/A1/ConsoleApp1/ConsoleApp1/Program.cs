using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Data;
using System.Data.SqlClient;

namespace ConsoleApp4
{
    class Program
    {
        static void Main(string[] args)
        {
            string conString = "Data Source=DESKTOP-MAP495M;Initial Catalog=Discord;Integrated Security=true;";

            SqlConnection con = new SqlConnection(conString);

            con.Open();
            string strDiscord = "SELECT * FROM Channels";
            SqlCommand cmd = new SqlCommand(strDiscord, con);

            Console.WriteLine("using SqlDataReader:");
            using (SqlDataReader reader = cmd.ExecuteReader())
            {
                while(reader.Read())
                {
                    Console.WriteLine("{0}, {1}", reader[0], reader[1]);
                }
            }

            con.Close();

            Console.WriteLine("\n");
            Console.WriteLine("using SqlDataAdapter and DataSet:");

            SqlDataAdapter daDiscord = new SqlDataAdapter(strDiscord, con);
            DataSet dset = new DataSet();

            daDiscord.Fill(dset, "Channels");
            foreach(DataRow pRow in dset.Tables["Channels"].Rows)
            {
                Console.WriteLine("{0}, {1}", pRow["Channel_Id"], pRow["Name"]);
            }
        }
    }
}