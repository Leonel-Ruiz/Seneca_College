using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.Mvc;

namespace S2021A1LSRN.Controllers
{
    public class HomeController : Controller
    {
        // Reference to the data manager
        private Manager m = new Manager();

        public ActionResult Index()
        {
            return View();
        }

        public ActionResult About()
        {
            ViewBag.Message = "Website Description";

            return View();
        }

        public ActionResult Contact()
        {
            ViewBag.Message = "Hi, my name is Leonel Said Ruiz Navarrete";

            return View();
        }
    }
}