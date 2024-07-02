using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

using System.Data.SqlClient;

namespace Lab_1
{
    public partial class Form1 : Form
    {
        SqlConnection conn;
        SqlDataAdapter usersDataAdapter;
        SqlDataAdapter postsDataAdapter;
        DataSet dset;
        BindingSource usersBindingSource;
        BindingSource postsBindingSource;

        SqlCommandBuilder cmdBuilder;

        string queryUsers, queryPosts;  

        public Form1()
        {
            InitializeComponent();

            FillData();
        }

        void FillData()
        {
            conn = new SqlConnection(getConnectionString());

            queryUsers = "SELECT * FROM Users";
            queryPosts = "SELECT * FROM Posts";

            usersDataAdapter = new SqlDataAdapter(queryUsers, conn);
            postsDataAdapter = new SqlDataAdapter(queryPosts, conn);

            dset = new DataSet();

            usersDataAdapter.Fill(dset, "Users");
            postsDataAdapter.Fill(dset, "Posts");

            cmdBuilder = new SqlCommandBuilder(postsDataAdapter);

            dset.Relations.Add("UserPost",
                dset.Tables["Users"].Columns["userID"],
                dset.Tables["Posts"].Columns["userID"]);

            this.UsersDataGrid.DataSource = dset.Tables["Users"];
            this.PostsDataGrid.DataSource = this.UsersDataGrid.DataSource;
            this.PostsDataGrid.DataMember = "UserPost";

            cmdBuilder.GetUpdateCommand();
        }

        private void label2_Click(object sender, EventArgs e)
        {

        }

        private void label1_Click(object sender, EventArgs e)
        {

        }

        private void button1_Click(object sender, EventArgs e)
        {
            try
            {
                postsDataAdapter.Update(dset, "Posts");
            }   
            
            catch (Exception ex)
            {
                MessageBox.Show("Database operation failed!\n" + ex.Message,
                    "Error",
                    MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }

        public string getConnectionString()
        {
            return "Data Source=NARCIS\\SQLEXPRESS02;" +
                "Initial Catalog=Github;Integrated Security=true;";
        }
    }
}
