using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using FirstApplication.Models;
using FirstApplication.Utils;
using Microsoft.AspNetCore.Mvc;

namespace FirstApplication.Controllers
{
    public class RowCountController : Controller
    {
        private readonly Repository _repository;
        private readonly DataContext _dataContext;
        public RowCountController(
                Repository repository,
                DataContext dataContext)
        {
            _repository = repository;
            _dataContext = dataContext;
        }
        public IActionResult Index()
        {
            var viewModel = new RowCountViewModel { DataContextCount=_dataContext.RowCount,RepositoryCount=_repository.RowCount};
            return View(viewModel);
        }
    }
}
