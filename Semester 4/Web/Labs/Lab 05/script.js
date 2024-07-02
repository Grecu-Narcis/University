function createMenu() {
    let menu = document.getElementById('menu');
    menu.classList.add('display-row');

    let subMenuSize = [3, 4, 5, 3, 4]

    for (let i = 0; i < 5; i++)
        menu.appendChild(createSubMenu("Option " + (i + 1), subMenuSize[i], "option"+(i + 1)));

    let resetButton = document.createElement('button');
    resetButton.textContent = 'Reset';
    resetButton.padding = '10px';

    document.getElementById('main').appendChild(resetButton);

    resetButton.addEventListener('click', () => {
        allHidden.forEach(divs => {
            divs.forEach(div => {
                div.classList.remove('hidden');
            });
        });

        allHidden = [];
    });
}

let allHidden = [];

function createSubMenu(menuName, numberOfOptions, divId) {
    let subMenuContainer = document.createElement('div');
    let subMenuTitle = document.createElement('div');
    let subMenuContent = document.createElement('div');

    subMenuContainer.style.padding = '10px';
    subMenuContainer.style.fontSize = '14pt';

    for (let i = 0; i < numberOfOptions; i++)
    {
        let subMenuOption = document.createElement('div');
        subMenuOption.innerHTML = 'Option ' + (i + 1);
        subMenuOption.classList.add('option'+(i + 1));
        subMenuOption.style.padding = '5px';
        subMenuOption.style.fontSize = '12pt';

        subMenuContent.appendChild(subMenuOption);
    }

    subMenuTitle.textContent = menuName;
    subMenuTitle.id = divId;

    subMenuContent.classList.add('hidden');

    subMenuTitle.addEventListener('mouseover', () => {
        subMenuContent.classList.remove('hidden');
        subMenuContent.classList.add('displayed');
    });

    subMenuTitle.addEventListener('mouseout', () => {
        subMenuContent.classList.remove('displayed');
        subMenuContent.classList.add('hidden');
    });

    subMenuTitle.addEventListener('click', () => {
        let divsToHide = document.querySelectorAll('.' + divId);
        console.log(divsToHide);
        divsToHide.forEach(div => {
            div.classList.add('hidden');
        });

        allHidden.push(divsToHide);
        console.log(allHidden);
    })

    subMenuContent.addEventListener('mouseover', () => {
        subMenuContent.classList.remove('hidden');
        subMenuContent.classList.add('displayed');
    });

    subMenuContent.addEventListener('mouseout', () => {
        subMenuContent.classList.remove('displayed');
        subMenuContent.classList.add('hidden');
    });


    subMenuContainer.appendChild(subMenuTitle);
    subMenuContainer.appendChild(subMenuContent);

    return subMenuContainer;
}

document.addEventListener('DOMContentLoaded', createMenu);