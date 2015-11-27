#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <Python.h>
#include <mutex>
#include <deque>
#include <string>
#include <QTimer>
#include <QListWidgetItem>

#include "glcanvas.hpp"
#include "stage.hpp"

namespace Ui {
class MainWindow;
}

struct BufferRequestMessage {
    std::string var_name_str;
    PyObject* py_buffer;
    int width_i;
    int height_i;
    int channels;
    int type;
    int step;
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    void plot_buffer(BufferRequestMessage& buff);
    ~MainWindow();

    void show();

    void draw();

    void resize_callback(int w, int h);

    void scroll_callback(float delta);

    void get_observed_variables(PyObject* observed_set);

    void reset_ac_min_labels();
    void reset_ac_max_labels();

    void mouse_drag_event(int mouse_x, int mouse_y);

public Q_SLOTS:
    void loop();
    void buffer_selected(QListWidgetItem * item);

    void ac_red_min_update();
    void ac_red_max_update();
    void ac_green_min_update();
    void ac_green_max_update();
    void ac_blue_min_update();
    void ac_blue_max_update();

    void ac_min_reset();
    void ac_max_reset();

    void ac_toggle();

    void recenter_buffer();

    void link_views_toggle();

private:
    QTimer update_timer_;
    Stage* currently_selected_stage_;
    std::map<std::string, PyObject*> held_buffers_;
    std::mutex mtx_;
    std::deque<BufferRequestMessage> pending_updates_;
    Ui::MainWindow *ui_;
    bool ac_enabled_;
    bool link_views_enabled_;
    std::map<std::string, std::shared_ptr<Stage>> stages_;

    QListWidgetItem* generateListItem(BufferRequestMessage&);
    void set_ac_min_value(int idx, float value);
    void set_ac_max_value(int idx, float value);
};

#endif // MAINWINDOW_H