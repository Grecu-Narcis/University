it('test-login-with-valid-credentials', function() {
  cy.visit('http://localhost:3000/login');
  cy.get(':nth-child(1) > [data-testid="form-entry-input"]').clear();
  cy.get(':nth-child(1) > [data-testid="form-entry-input"]').type('narcis@gmail.com');
  cy.get(':nth-child(2) > [data-testid="form-entry-input"]').clear();
  cy.get(':nth-child(2) > [data-testid="form-entry-input"]').type('cocos123');
  cy.get('.login-options > [data-testid="button-test-id"]').click();

  cy.url().should('include', '/cars/1');

  cy.get('[href="/dashboard"]').should('have.text', 'Dashboard');
  cy.get('.links > [href="/home"]').should('have.text', 'Home');
  cy.get('[data-testid="username"]').should('have.text', 'Narcis Grecu');
});