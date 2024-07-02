import { ComponentFixture, TestBed } from '@angular/core/testing';

import { ViewCartPageComponent } from './view-cart-page.component';

describe('ViewCartPageComponent', () => {
  let component: ViewCartPageComponent;
  let fixture: ComponentFixture<ViewCartPageComponent>;

  beforeEach(async () => {
    await TestBed.configureTestingModule({
      imports: [ViewCartPageComponent]
    })
    .compileComponents();
    
    fixture = TestBed.createComponent(ViewCartPageComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
