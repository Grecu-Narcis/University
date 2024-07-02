it('test-login-wrong-data', function() {
  cy.visit('http://localhost:3000/login');
  cy.get('[data-testid="login-welcome-message"]').should('have.class', 'login-welcome-message');
  cy.get('[data-testid="login-welcome-message"]').should('have.text', 'Welcome to Rentify');
  cy.get('.login-message').should('have.text', 'Sign in to your account');
  cy.get(':nth-child(1) > [data-testid="form-entry-input"]').type('wrong');
  cy.get(':nth-child(2) > [data-testid="form-entry-input"]').clear();
  cy.get(':nth-child(2) > [data-testid="form-entry-input"]').type('wrong');
  cy.get('.login-options > [data-testid="button-test-id"]').click();
  cy.get('[data-testid="error-message"] > div').should('be.visible');
  cy.get('[data-testid="register-link"]').should('be.visible');
  cy.get('[data-testid="register-link"]').click();
  cy.url().should('include', '/register');
});