describe('template spec', () => {
  it('passes', () => {
    cy.visit('http://localhost:3000/home')
    cy.get('[data-testid="welcome-header"]').should('exist');
    cy.get('[data-testid="welcome-message"]').should('exist');
    cy.contains('Start renting now').should('exist');
    cy.get('[data-testid="landing-info"]').should('exist');
  })
})