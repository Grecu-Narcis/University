import { ComponentFixture, TestBed } from '@angular/core/testing';

import { SnakeBoardComponent } from './snake-board.component';

describe('SnakeBoardComponent', () => {
  let component: SnakeBoardComponent;
  let fixture: ComponentFixture<SnakeBoardComponent>;

  beforeEach(async () => {
    await TestBed.configureTestingModule({
      imports: [SnakeBoardComponent]
    })
    .compileComponents();
    
    fixture = TestBed.createComponent(SnakeBoardComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
