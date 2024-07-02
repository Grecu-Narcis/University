import '@testing-library/jest-dom';
import { render, screen } from '@testing-library/react';
import { expect, test } from 'vitest';
import { FormEntry } from '../features/CRUD Operations/User Form/Form Entry/FormEntry';

import React from 'react';

test('test form entry without default value', () => {
    const demoReference = React.createRef<HTMLInputElement>();

    render(<FormEntry label='test-label' placeHolder='test-placeHolder' defaultValue='' ref={demoReference} />);

    const element = screen.getByTestId('form-entry');
    expect(element).toBeInTheDocument();
});

test('test form entry with default value', () => {
    const demoReference = React.createRef<HTMLInputElement>();

    render(<FormEntry label='test-label' placeHolder='test-placeHolder' defaultValue='test value' ref={demoReference} />);

    const element = screen.getByTestId('form-entry');
    expect(element).toBeInTheDocument();
});

test('test form entry for enabled input', () => {
    const demoReference = React.createRef<HTMLInputElement>();

    render(<FormEntry label='test-label' placeHolder='test-placeHolder' defaultValue='test value' ref={demoReference} />);

    const element = screen.getByTestId('form-entry-input');
    expect(element).toBeEnabled();
});
