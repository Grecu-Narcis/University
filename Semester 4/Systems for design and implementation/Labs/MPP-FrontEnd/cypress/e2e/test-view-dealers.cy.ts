it('test-view-dealers', function() {
  cy.visit('http://localhost:3000/login');
  cy.get(':nth-child(1) > [data-testid="form-entry-input"]').clear();
  cy.get(':nth-child(1) > [data-testid="form-entry-input"]').type('user@user.com');
  cy.get(':nth-child(2) > [data-testid="form-entry-input"]').clear();
  cy.get(':nth-child(2) > [data-testid="form-entry-input"]').type('user');
  cy.get('.login-options > [data-testid="button-test-id"]').click();
  cy.get('h1').should('have.text', 'Dealers');
  cy.get('.search-bar').should('be.visible');
  cy.get('.navbar').click();
  cy.get('.search-bar').clear();
  cy.get('.search-bar').type('tes');
  cy.get('.infinite-scroll-component').should('have.class', 'infinite-scroll-dealers');
  cy.get('.search-bar').clear();
  cy.get('.search-bar').type('test');
  cy.get('.not-found-message').should('have.text', 'No dealer found!');
});