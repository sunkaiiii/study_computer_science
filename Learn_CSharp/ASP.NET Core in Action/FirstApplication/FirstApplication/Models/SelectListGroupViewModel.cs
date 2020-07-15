using System;
using System.Collections.Generic;
using Microsoft.AspNetCore.Mvc.Rendering;

namespace FirstApplication.Models
{
    public class SelectListGroupViewModel
    {
        public IEnumerable<string> SelectedValues { get; set; }
        public IEnumerable<SelectListItem> ItemsWithGroups { get; set; }
        public SelectListGroupViewModel()
        {
            var dynamic = new SelectListGroup { Name = "Dynamic" };
            var stat = new SelectListGroup { Name = "Static" };
            ItemsWithGroups = new List<SelectListItem>
            {
                new SelectListItem
                {
                    Value = "js",
                    Text = "Javascript",
                    Group = dynamic
                },
                new SelectListItem
                {
                    Value = "cpp",
                    Text = "C++",
                    Group = stat
                },
                new SelectListItem
                {
                    Value = "python",
                    Text = "Python",
                    Group = dynamic
                },
                new SelectListItem
                {
                    Value = "csharp",
                    Text = "C#",
                },
            };
        }
    }
}
