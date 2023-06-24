using System.Windows.Forms;
using System.Data.SqlClient;
using System.Data;

namespace WinFormsApp1
{
    public partial class Form1 : Form
    {
        SqlConnection conn;
        SqlDataAdapter daCategories;
        SqlDataAdapter daCulturalEvents;
        DataSet dSet;
        BindingSource bsCategories;
        BindingSource bsCulturalEvents;

        SqlCommandBuilder cmdBuilder;

        string queryCategories;
        string queryCulturalEvents;
        public Form1()
        {
            InitializeComponent();
            FillData();
        }

        void FillData()
        {
            conn = new SqlConnection(getConnectionString());

            queryCategories = "SELECT * FROM Category";
            queryCulturalEvents = "SELECT * FROM CulturalEvent";

            daCategories = new SqlDataAdapter(queryCategories, conn);
            daCulturalEvents = new SqlDataAdapter(queryCulturalEvents, conn);
            dSet = new DataSet();
            daCategories.Fill(dSet, "Category");
            daCulturalEvents.Fill(dSet, "CulturalEvent");

            cmdBuilder = new SqlCommandBuilder(daCulturalEvents);

            dSet.Relations.Add("CategoryCulturalEvents",
                dSet.Tables["Category"].Columns["CategoryID"],
                dSet.Tables["CulturalEvent"].Columns["CategoryID"]);

            bsCategories = new BindingSource();
            bsCategories.DataSource = dSet.Tables["Category"];
            bsCulturalEvents = new BindingSource(bsCategories, "CategoryCulturalEvents");

            dgvCategories.DataSource = bsCategories;
            dgvCulturalEvents.DataSource = bsCulturalEvents;
        }

        string getConnectionString()
        {
            return "Data Source=DESKTOP-MAP495M;Initial Catalog=exam_dbms;Integrated Security=true;";
        }

        private void Form1_Load(object sender, EventArgs e)
        {

        }

        private void label1_Click(object sender, EventArgs e)
        {

        }

        private void button1_Click_1(object sender, EventArgs e)
        {
            try
            {
                cmdBuilder.GetUpdateCommand();

                daCulturalEvents.Update(dSet, "CulturalEvent");
                MessageBox.Show("Changes saved successfully.");
            }
            catch (SqlException ex)
            {
                MessageBox.Show(ex.Message);
            }
        }

        private void label2_Click(object sender, EventArgs e)
        {

        }
    }
}