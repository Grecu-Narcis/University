/* ==== Test Created with Cypress Studio ==== */
it('test-register-page', function() {
  /* ==== Generated with Cypress Studio ==== */
  cy.visit('http://localhost:3000/register');
  cy.get('[data-testid="register-message"]').should('have.text', 'Create a new account');
  cy.get(':nth-child(1) > .form-label').click();
  cy.get(':nth-child(1) > [data-testid="form-entry-input"]').click();
  cy.get(':nth-child(1) > [data-testid="form-entry-input"]').should('have.class', 'form-input');
  cy.get(':nth-child(1) > [data-testid="form-entry-input"]').should('be.enabled');
  cy.get(':nth-child(2) > [data-testid="form-entry-input"]').click();
  cy.get(':nth-child(2) > [data-testid="form-entry-input"]').should('be.enabled');
  cy.get(':nth-child(3) > [data-testid="form-entry-input"]').should('be.enabled');
  cy.get(':nth-child(4) > [data-testid="form-entry-input"]').should('be.enabled');
  cy.get('[data-testid="register-button"]').should('have.text', 'Register');
  cy.get('[data-testid="register-button"]').click();
  cy.get(':nth-child(1) > [data-testid="form-entry-input"]').type('test');
  cy.get(':nth-child(2) > [data-testid="form-entry-input"]').clear();
  cy.get(':nth-child(2) > [data-testid="form-entry-input"]').type('test');
  cy.get(':nth-child(3) > [data-testid="form-entry-input"]').clear();
  cy.get(':nth-child(3) > [data-testid="form-entry-input"]').type('test1234@gmail.com');
  cy.get(':nth-child(4) > [data-testid="form-entry-input"]').clear();
  cy.get(':nth-child(4) > [data-testid="form-entry-input"]').type('cocos123');
  cy.get('[data-testid="register-button"]').click();
  /* ==== End Cypress Studio ==== */
});