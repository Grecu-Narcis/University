import { ComponentFixture, TestBed } from '@angular/core/testing';

import { SelectCategoryPageComponent } from './select-category-page.component';

describe('SelectCategoryPageComponent', () => {
  let component: SelectCategoryPageComponent;
  let fixture: ComponentFixture<SelectCategoryPageComponent>;

  beforeEach(async () => {
    await TestBed.configureTestingModule({
      imports: [SelectCategoryPageComponent]
    })
    .compileComponents();
    
    fixture = TestBed.createComponent(SelectCategoryPageComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
