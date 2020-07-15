using System;
using System.Collections.Generic;
using Microsoft.AspNetCore.Mvc.Rendering;

namespace FirstApplication.Models
{
    //view model for displaying select element dropdowns and list boxes
    public class SelectListsViewModel
    {
        public string SelectedValue1 { get; set; }
        public string SelectedValue2 { get; set; }
        public IEnumerable<string> MultiValues { get; set; }

        public IEnumerable<SelectListItem> Items { get; set; } = new List<SelectListItem>
        {
            new SelectListItem{Value= "csharp", Text="C#"},
            new SelectListItem{Value= "python", Text= "Python"},
            new SelectListItem{Value= "cpp", Text="C++"},
            new SelectListItem{Value= "java", Text="Java"},
            new SelectListItem{Value= "js", Text="JavaScript"},
            new SelectListItem{Value= "ruby", Text="Ruby"},
        };
    }
}
