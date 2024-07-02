import { Component } from '@angular/core';
import { BackendService } from '../../services/BackendService';
import { Router } from '@angular/router';
import { FormsModule } from '@angular/forms';

@Component({
  selector: 'app-select-category-page',
  standalone: true,
  imports: [FormsModule],
  templateUrl: './select-category-page.component.html',
  styleUrl: './select-category-page.component.css'
})
export class SelectCategoryPageComponent {
  selectedCategory: any = 'default';
  categoriesList: string[] = [];

  constructor(private backendService: BackendService, private router: Router) {
  }

  ngOnInit(): void {
    if (localStorage.getItem('userId') === null) {
      this.router.navigate(['/login']);
    }

    this.backendService.getCategories().subscribe((data: any[]) => {
      this.categoriesList = data.map((current) => current);
      console.log(this.categoriesList);
      this.selectedCategory = this.categoriesList[0];
    });
  }

  public onSelectCategory(): void {
    console.log(this.selectedCategory);
    this.router.navigate(['/viewProducts', this.selectedCategory]);
  }

}
