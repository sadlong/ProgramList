###  Button

需要导入：`import QtQuick.Controls 2.5 `

其实总的来说，Button其实就是Rectangle+MouseArea



**多个button保证只有一个button选中**

```json
//多个按钮 确保只有一个按钮是被选中的 在每个button中加上autoExclusive: true
Button {
    id: btn1
    width: 50
    height: 50
    autoExclusive: true
    checkable: true
}

Button {
    id: btn2
    width: 50
    height: 50
    x: 60
    autoExclusive: true
    checkable: true
}

Button {
    id: btn3
    width: 50
    height: 50
    x: 120
    autoExclusive: true
    checkable: true
}
```

